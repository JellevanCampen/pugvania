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
  e->Initialize();
  g_log("Starting the game.", log::kLog_Game);
  e->Start();
  e->Stop();
  e->Terminate();

  return 0;
}