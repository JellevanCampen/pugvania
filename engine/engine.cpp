#include "engine.h"
#include <iostream>
#include "engine_config.h"

namespace engine {

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
  while (is_running_) {
    Update();
    Draw();
  }
}

void Engine::Update() {
  // Update game timing information first, as it is used by all other updates. 
  game_time_.Update(time_step_micros_);
}

void Engine::Draw() {
  // Update game timing information first, as it is used by all other draws. 
  game_time_.Draw(0.0f);
}

} // namespace