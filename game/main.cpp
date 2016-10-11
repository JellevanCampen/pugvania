#include <iostream>
#include "engine.h"
#include "game_config.h"

using namespace::engine;

int main()
{
  std::cout << "Running Pugvania" << std::endl;
  std::cout << "Version: "
    << GAME_VERSION_MAJOR << "."
    << GAME_VERSION_MINOR << "."
    << GAME_VERSION_PATCH << "."
    << GAME_VERSION_TWEAK
    << std::endl;

  Engine* e = Engine::get();
  g_log("Starting the game.", log::kGame);
  e->Start();

  std::cout << "Press enter to terminate the game... ";
  std::cin.get();

  return 0;
}