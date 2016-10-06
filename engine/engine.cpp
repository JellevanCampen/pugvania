#include "engine.h"
#include <iostream>
#include <algorithm>
#include "engine_config.h"
#include "utility\patterns\reverse_iterator.h"

namespace engine {

Engine::~Engine() {
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
}

void Engine::Start() {
  // TODO(Jelle): load the game loop settings from a configuration file. 

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
  // TODO(Jelle): load the engine configuration from a configuration file. 
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
    update_rate_ = (update_rate_ * (update_rate_sample_ - 1) + (update_rate_current)) / update_rate_sample_;
  }
}

void Engine::SampleDrawRate() {
  if (game_time_.draw_count_ % draw_rate_sample_ == 0) {
    TimePointMicros now = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros elapsed = (now - draw_rate_sample_time_);
    draw_rate_sample_time_ = now;
    float draw_rate_current = draw_rate_sample_ * 1000000.0f / ((float)elapsed.count());
    draw_rate_ = (draw_rate_ * (draw_rate_sample_ - 1) + (draw_rate_current)) / draw_rate_sample_;
  }
}

} // namespace