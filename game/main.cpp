#include <iostream>
#include "engine.h"
#include "game_config.h"

#include "common\datatypes\shape_types.h"

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

  Point2Df p1(3.0f, 2.0f);
  Point2Df p2(2.0f, 5.0f);
  Vector2Df v1(10.0f, 20.0f);
  Vector2Df vx(1.0f, 0.0f);
  Line2Df l1(p1, p2);

  std::cout << p1 << ", " << p2 << ", " << v1 << std::endl;
  std::cout << p2 - p1 << std::endl;
  std::cout << p2 + (p2 - p1) << ", " << (p1 == (p2 + (p2 - p1))) << std::endl;
  std::cout << v1.Length() << std::endl;
  std::cout << v1.ScalarProduct(v1) << std::endl;
  std::cout << v1.Normalize() << std::endl;
  std::cout << v1.Project(vx) << std::endl;
  std::cout << v1.Reflect(vx) << std::endl;
  std::cout << l1 << std::endl;
  std::cout << l1 + v1 << std::endl;
  std::cout << l1.Direction() << std::endl;
  std::cout << l1.Normal() << std::endl;
  std::cout << l1.Direction().Rotate(3.141592f / 2) << std::endl;

  Engine::Create();
  g_log("Starting the game.", log::kGame);
  g_engine->Start();
  Engine::Destroy();

  std::cout << "Press enter to terminate the game... ";
  std::cin.get();

  return 0;
}