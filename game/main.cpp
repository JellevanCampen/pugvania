#include <iostream>
#include "engine.h"
#include "game_config.h"

int main()
{
  std::cout << "Running Pugvania" << std::endl;
  std::cout << "Version: "
    << GAME_VERSION_MAJOR << "."
    << GAME_VERSION_MINOR << "."
    << GAME_VERSION_PATCH << "."
    << GAME_VERSION_TWEAK
    << std::endl;

  Engine::Engine engine;
  engine.Initialize();
  engine.Start();
  engine.Stop();
  engine.Terminate();
  
  std::cin;

  return 0;
}