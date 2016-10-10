#include "engine.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"
#include "engine_config.h"
#include "utility\patterns\reverse_iterator.h"

namespace engine {

// Global reference to the Engine to make it more easily available. Note that 
// this ease of access comes at the cost of safety. Accessing this global 
// pointer before the Engine is created will return a nullpointer. 
Engine* g_engine{ NULL };

void g_log(std::string message, LogID channels) {
  g_engine->logging->Log(message, channels);
}

Engine* Engine::get() {
  // Construct the engine and all subsystems. 
  static Engine instance;
  g_engine = &instance;

  // Initialize the engine and all subsystems automatically.
  instance.Initialize();

  return g_engine;
}

Engine::~Engine() {
  // Terminate the engine and all subsystems automatically on destruction.
  Terminate();

  // This is where all subsystems are freed. 
  for (EngineSubsystem* subsystem : subsystems_)
    delete subsystem;
}

void Engine::Initialize()	{
  // Note that standard console output is used here as the logging subsystem 
  // is not initialized yet. 
  std::cout << "Initializing Engine." << std::endl;
  std::cout << "Version: " 
    << ENGINE_VERSION_MAJOR << "."
    << ENGINE_VERSION_MINOR << "."
    << ENGINE_VERSION_PATCH << "."
    << ENGINE_VERSION_TWEAK
    << std::endl;

#ifdef PF_WINDOWS 
  std::cout << "Target platform: Windows" << std::endl;
#endif
#ifdef PF_LINUX 
  std::cout << "Target platform: Linux" << std::endl;
#endif
#ifdef PF_APPLE
  std::cout << "Target platform: Apple" << std::endl;
#endif
#ifdef PF_UNKNOWN 
  std::cout << "Target platform: Unknown" << std::endl;
#endif

  // Initialize all engine subsystems in forward order. Note that this 
  // initialization order is important to avoid dependency issues between 
  // subsystems. 
  for (EngineSubsystem* subsystem : subsystems_)
    subsystem->Initialize();

  // Set the shorthand access pointers for all subsystems.
  logging = subsystem_logging_;

  // Load the engine configuration from engine_config.ini
  LoadEngineConfig();

  const void* engine_adress = static_cast<const void*>(this);
  std::stringstream init_message;
  init_message << "Engine initialized at 0x" << engine_adress;
  g_log(init_message.str(), log::kEngine);
}

void Engine::Start() {
  // Initialize the update and draw rate sampling times so that both rates can  
  // be measured from this point on. 
  update_rate_sample_time_ = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
  draw_rate_sample_time_ = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());

  is_running_ = true;
  RunGameLoop();
}

void Engine::Stop() {
  is_running_ = false;
}

void Engine::LoadEngineConfig()
{
  boost::property_tree::ptree pt;
  try { 
    // TODO(Jelle): the path to the config directory should be loaded from the path configuration file
    boost::property_tree::ini_parser::read_ini("../../code/config/engine_config.ini", pt);
    drawing_is_enabled_ = pt.get<bool>("engine.drawing_is_enabled", true);
    update_time_step_is_fixed_ = pt.get<bool>("engine.update_time_step_is_fixed" , true);
    time_step_micros_ = pt.get<unsigned int>("engine.time_step_micros", 1000000/60);
    draw_rate_is_capped_ = pt.get<bool>("engine.draw_rate_is_capped", false);
    max_frame_skip_ = pt.get<unsigned short int>("engine.max_frame_skip", 5);
    update_rate_sample_ = pt.get<unsigned short int>("engine.update_rate_sample", 10);
    draw_rate_sample_ = pt.get<unsigned short int>("engine.draw_rate_sample", 10);
    rate_rolling_average_window_ = pt.get<unsigned short int>("engine.rate_rolling_average_window", 4);
  } catch (boost::property_tree::ini_parser_error err) {
    std::stringstream warning_message;
    warning_message << "Error reading engine config, using default values. File ("
      << err.filename()
      << " at line "
      << err.line()
      << "): "
      << err.message();
    g_log(warning_message.str(), log::kWarning);
  }
}

void Engine::Terminate() {
  std::cout << "Terminating Engine." << std::endl;

  // Reset the shorthand access pointers for all subsystems to nullpointers.
  logging = NULL;

  // Terminate all engine subsystems in reverse order. Note that this 
  // termination order is important to avoid dependency issues between 
  // subsystems. 
  for (EngineSubsystem* subsystem : reverse(subsystems_))
    subsystem->Terminate();
}

Engine::Engine() {
  // This is where all subsystems are dynamically allocated.
  subsystem_logging_ = new Logging();
  subsystems_.push_back(subsystem_logging_);
}

void Engine::RunGameLoop() {
  DurationMicros time_step_micros{ time_step_micros_ };
  TimePointMicros time_previous = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
  DurationMicros lag{ 0 };
  bool update_drawn{ false };

  while (is_running_) {
    TimePointMicros time_current = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros time_since_last_update = (time_current - time_previous);
    time_previous = time_current;

    if (update_time_step_is_fixed_) {
      // Fixed time step loop. The principle: update once, then keep drawing 
      // until its time for another update. Settings: "drawing enabled vs 
      // disabled", "capped vs uncapped framerate", and "maximum frameskip" 
      // can cause slight deviations from this behavior. 
      lag += time_since_last_update;
      unsigned short int frame_skip_counter{ 0 };
      while (lag >= time_step_micros && frame_skip_counter <= max_frame_skip_) {
        Update(time_step_micros_);
        lag -= time_step_micros;
        frame_skip_counter++;
        update_drawn = false;
        SampleUpdateRate();
      }

      if (drawing_is_enabled_ && (!draw_rate_is_capped_ || !update_drawn)) {
        Draw(std::min(1.0f, ((float)lag.count()) / ((float)time_step_micros_)));
        update_drawn = true;
        SampleDrawRate();
      }
    } else {
      // Variable time step loop. The principle: perform updates succeeded by 
      // draws as fast as possible. Setting: "drawing enabled vs disabled",  
      // can cause a slight deviation from this behavior. 
      Update(time_since_last_update.count());
      SampleUpdateRate();
      if (drawing_is_enabled_) {
        Draw(0.0f);
        SampleDrawRate();
      }
    }
    
  }
}

void Engine::Update(unsigned int delta_time_micros) {
  // Update game timing information first, as it is used by all other updates. 
  game_time_.Update(delta_time_micros);

  // Update all engine subsystems in forward order.
  for (EngineSubsystem* subsystem : subsystems_)
    subsystem->Update();
}

void Engine::Draw(float frame_interpolation) {
  // Update game timing information first, as it is used by all other draws. 
  game_time_.Draw(frame_interpolation);

  // Draw all engine subsystems in forward order.
  for (EngineSubsystem* subsystem : subsystems_)
    subsystem->Draw();
}

void Engine::SampleUpdateRate() {
  if (game_time_.update_count_ % update_rate_sample_ == 0) {
    TimePointMicros now = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros elapsed = (now - update_rate_sample_time_);
    update_rate_sample_time_ = now;
    float update_rate_current = update_rate_sample_ * 1000000.0f / ((float)elapsed.count());
    update_rate_ = (update_rate_ * (rate_rolling_average_window_ - 1) + (update_rate_current)) / rate_rolling_average_window_;
  }
}

void Engine::SampleDrawRate() {
  if (game_time_.draw_count_ % draw_rate_sample_ == 0) {
    TimePointMicros now = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros elapsed = (now - draw_rate_sample_time_);
    draw_rate_sample_time_ = now;
    float draw_rate_current = draw_rate_sample_ * 1000000.0f / ((float)elapsed.count());
    draw_rate_ = (draw_rate_ * (rate_rolling_average_window_ - 1) + (draw_rate_current)) / rate_rolling_average_window_;
  }
}

} // namespace