#include "engine.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"
#include "engine_config.h"
#include "common/patterns/reverse_iterator.h"

namespace engine {

Engine* g_engine{ NULL };

void g_log(std::string message, LogID channels) {
  g_engine->logging->Log(message, channels);
}

void Engine::Create() {
  // Create the engine and all its subsystems in forward order.
  g_engine = new Engine();
  g_engine->CreateSubsystems();

  // Initialize the engine and all subsystems in forward order.
  g_engine->Initialize();
}

void Engine::Destroy() {
  // Terminate all subsystems and the engine in reverse order. 
  g_engine->Terminate();

  // Destroy all subsystems and the engine in reverse order.
  g_engine->DestroySubsystems();
  delete g_engine;
  g_engine = NULL;
}

void Engine::Start() {
  is_running_ = true;
  RunGameLoop();
}

void Engine::Stop() {
  is_running_ = false;
}

void Engine::CreateSubsystems() {
  // Creation in forward order.
  path = new Path();
  subsystems_.push_back(path);
  logging = new Logging();
  subsystems_.push_back(logging);
  timing = new Timing();
  subsystems_.push_back(timing);
  graphics = new GraphicsBootstrapper();
  subsystems_.push_back(graphics);
}

void Engine::DestroySubsystems() {
  // Destruction in reverse order.
  delete graphics;
  graphics = NULL;
  delete timing;
  timing = NULL;
  delete logging;
  logging = NULL;
  delete path;
  path = NULL;

  subsystems_.clear();
}

void Engine::Initialize() {
  // Note: console output is used here as the logging subsystem is not 
  // initialized yet. 
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

  // Initialize all subsystems in forward order. 
  


  for (EngineSubsystem*& subsystem : subsystems_) {
    EngineSubsystem* address = subsystem->Initialize();
    subsystem = address;
    LogInitializationMessage(address);
  }

  // Load the engine configuration from engine_config.ini
  LoadConfiguration();

  // Log a message on initialization.
  const void* engine_adress = static_cast<const void*>(this);
  std::stringstream init_message;
  init_message << "Engine initialized at 0x" << engine_adress << ".";
  g_log(init_message.str(), log::kEngine);
}

void Engine::Terminate() {
  // Log a message on termination.
  g_log("Engine terminating.", log::kEngine);

  // Terminate all subsystems in reverse order.
  for (EngineSubsystem*& subsystem : reverse(subsystems_)) {
    subsystem->Terminate();
    LogTerminationMessage(subsystem);
  }
}

void Engine::LogInitializationMessage(EngineSubsystem* subsystem) {
  const void* adress = static_cast<const void*>(subsystem);
  std::stringstream message;
  message << subsystem->GetName() << " subsystem initialized at 0x" << adress << ".";

  // Only use the logger when the logging subsystem has been initialized. 
  if (logger_initialized_ == true)
    g_log(message.str(), log::kEngine);
  else if (subsystem->GetName().compare("Logging") == 0) {
    g_log(message.str(), log::kEngine);
    logger_initialized_ = true;
  } else {
    std::cout << message.str() << std::endl;
  }
}

void Engine::LogTerminationMessage(EngineSubsystem* subsystem) {
  std::stringstream message;
  message << subsystem->GetName() << " subsystem terminated.";

  // Only use the logger when the logging subsystem has been initialized. 
  if (logger_initialized_ == false) 
    std::cout << message.str() << std::endl;
  else if (subsystem->GetName().compare("Logging") == 0) {
    std::cout << message.str() << std::endl;
    logger_initialized_ = false;
  } else
    g_log(message.str(), log::kEngine);
}

void Engine::LoadConfiguration()
{
  ConfigFile engine_config((*g_engine->path)["config"] + "engine_config.ini", ConfigFile::WARN_COUT, ConfigFile::WARN_COUT);
  engine_config.ReadProperty<bool>("engine.drawing_is_enabled", &drawing_is_enabled_, true);
  engine_config.ReadProperty<bool>("engine.update_time_step_is_fixed", &update_time_step_is_fixed_, true);
  engine_config.ReadProperty<unsigned int>("engine.time_step_micros", &time_step_micros_, 1000000 / 60);
  engine_config.ReadProperty<bool>("engine.draw_rate_is_capped", &draw_rate_is_capped_, false);
  engine_config.ReadProperty<unsigned short int>("engine.max_frame_skip", &max_frame_skip_, 5);
}

void Engine::RunGameLoop() {
  DurationMicros time_step_micros{ time_step_micros_ };
  TimePointMicros time_previous = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
  DurationMicros lag{ 0 };
  bool update_drawn{ false };

  timing->PassStartSignal();

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
      }

      if (drawing_is_enabled_ && (!draw_rate_is_capped_ || !update_drawn)) {
        Draw(std::min(1.0f, ((float)lag.count()) / ((float)time_step_micros_)));
        update_drawn = true;
      }
    } else {
      // Variable time step loop. The principle: perform updates succeeded by 
      // draws as fast as possible. Setting: "drawing enabled vs disabled",  
      // can cause a slight deviation from this behavior. 
      Update(time_since_last_update.count());
      if (drawing_is_enabled_) {
        Draw(0.0f);
      }
    }
  }
}

void Engine::Update(unsigned long long delta_time_micros) {
  timing->PassUpdateTimingInfo(delta_time_micros);

  // Update all engine subsystems in forward order.
  for (EngineSubsystem* subsystem : subsystems_)
    subsystem->Update();

  // TODO(Jelle): Remove this later. This is temporary code to shut down the 
  // engine after 5 seconds for debugging purposes.
  if (timing->GetTotalTimeMicros() >= 5000000)
    Stop();
  // TODO(Jelle): Remove this when the Timing is fully functional. This is 
  // temporary display rate measurement info. 
  if (timing->GetUpdateCount() % 60 == 0) {
    g_log("Updates per second: " + std::to_string(timing->GetUpdateRate()));
    g_log("Frames per second: " + std::to_string(timing->GetDrawRate()));
  }
}

void Engine::Draw(float frame_interpolation) {
  timing->PassDrawTimingInfo(frame_interpolation);

  // Draw all engine subsystems in forward order.
  for (EngineSubsystem* subsystem : subsystems_)
    subsystem->Draw();
}

} // namespace