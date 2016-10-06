#include <iostream>
#include "engine.h"
#include "game_config.h"

using namespace engine;

int main()
{
  std::cout << "Running Pugvania" << std::endl;
  std::cout << "Version: "
    << GAME_VERSION_MAJOR << "."
    << GAME_VERSION_MINOR << "."
    << GAME_VERSION_PATCH << "."
    << GAME_VERSION_TWEAK
    << std::endl;

  Engine* engine = Engine::get();
  engine->Initialize();
  // This is an example of shorthand access to subsystems of the engine. 
  engine->logging->Log("Starting the game loop.", log::kLog_Game);
  engine->Start();
  engine->Stop();
  engine->Terminate();
  
  std::cin;

  return 0;
}