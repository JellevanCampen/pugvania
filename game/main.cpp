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
  Point2Df p3{ p1.Interpolate(p2, 0.25f) };
  Vector2Df v1(10.0f, 20.0f);
  Vector2Df vx(1.0f, 0.0f);
  Line2Df l1(p1, p2);
  Rectangle2Df r1{ l1 };

  std::cout << "p1=" << p1 << ", p2=" << p2 << ", p3=" << p3 << ", v1=" << v1 << ", vx=" << vx << std::endl;
  std::cout << "Subtraction of points: " << p2 - p1 << std::endl;
  std::cout << "Subtraction of points and vectors: " << p2 - (p2 - p1) << ", Correct? " << (p1 == (p2 - (p2 - p1))) << std::endl;
  std::cout << "Vector length: " << v1.Length() << std::endl;
  std::cout << "Scalar product with self is length square: " << v1.ScalarProduct(v1) << std::endl;
  std::cout << "Normalize: " << v1.Normalize() << std::endl;
  std::cout << "Project on X-axis: " << v1.Project(vx) << std::endl;
  std::cout << "Reflect over X-axis: " << v1.Reflect(vx) << std::endl;
  std::cout << "l1=" << l1 << std::endl;
  std::cout << "Translated: " << l1 + v1 << std::endl;
  std::cout << "Direction vector: " << l1.Direction() << std::endl;
  std::cout << "Point on: " << l1[0.25f] << ", Correct? " << (l1[0.25f] == p3) << std::endl;
  std::cout << "Contains p1, p2, p3, and a random point? " << l1.Contains(p1) << ", " << l1.Contains(p2) << ", " << l1.Contains(p3) << ", " << l1.Contains(Point2Df(1.0f, 1.0f)) << std::endl;
  std::cout << "via Normal(): " << l1.Normal() << ", via Direction() and Rotate(): " << l1.Direction().Rotate(3.141592f / 2) << std::endl;
  std::cout << "Are equal? " << (l1.Normal() == l1.Direction().Rotate(3.1415926535897932384626433f / 2.0f)) << std::endl;
  std::cout << "r1=" << r1 << ", reordered: " << r1.ReorderPoints() << std::endl;
  std::cout << "Line on: " << r1[0.25f] << ", Point on: " << r1[0.25f][0.25f] << ", Correct? " << (r1[1.0f][0.0f].Interpolate(r1[0.0f][1.0f], 0.25f) == p3) << std::endl;

  Engine::Create();
  g_log("Starting the game.", log::kGame);
  g_engine->Start();
  Engine::Destroy();

  std::cout << "Press enter to terminate the game... ";
  std::cin.get();

  return 0;
}