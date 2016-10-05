#include "engine.h"
#include <iostream>
#include <algorithm>
#include "engine_config.h"

namespace engine {

typedef std::chrono::duration<unsigned int, std::micro> DurationMicros;
typedef std::chrono::time_point<std::chrono::high_resolution_clock, DurationMicros> TimePointMicros;

void Engine::Initialize()	{
  std::cout << "Initializing Engine." << std::endl;
  std::cout << "Version: " 
    << ENGINE_VERSION_MAJOR << "."
    << ENGINE_VERSION_MINOR << "."
    << ENGINE_VERSION_PATCH << "."
    << ENGINE_VERSION_TWEAK
    << std::endl;
}

void Engine::Start() {
  // TODO(Jelle): load the game loop settings from a configuration file. 

  is_running_ = true;
  RunGameLoop();
}

void Engine::Stop() {
  is_running_ = false;
}

void Engine::Terminate() {
  std::cout << "Terminating Engine." << std::endl;
}

void Engine::RunGameLoop() {
  // TODO(Jelle): implement the actual, flexible game loop.
  DurationMicros time_step_micros{ time_step_micros_ };
  TimePointMicros time_previous = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
  DurationMicros lag{ 0 };
  bool update_drawn{ false };

  while (is_running_) {
    TimePointMicros time_current = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros time_since_last_update = (time_current - time_previous);
    time_previous = time_current;
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
  }
}

void Engine::Update(unsigned int delta_time_micros) {
  // Update game timing information first, as it is used by all other updates. 
  game_time_.Update(delta_time_micros);

  // TODO(Jelle): Remove this when the flexible game loop is finilized. 
  std::cout << "Update (" << game_time_.GetUpdateCount() << "): total = " << game_time_.GetTotalTimeMicros() << ", delta = " << game_time_.GetDeltaTimeMicros() << std::endl;
}

void Engine::Draw(float frame_interpolation) {
  // Update game timing information first, as it is used by all other draws. 
  game_time_.Draw(frame_interpolation);

  // TODO(Jelle): Remove this when the flexible game loop is finilized. 
  std::cout << "Draw (" << game_time_.GetDrawCount() << "): total = " << game_time_.GetTotalTimeMicros() << ", interpolation = " << game_time_.GetFrameInterpolation() << std::endl;
}

} // namespace