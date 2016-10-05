#pragma once
#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

namespace engine {

// Encompasses all subsystems used to run the Game. It is responsible for 
// subsystem initialization and termination, as well as running the game loop.
class Engine {
  public:
  // Initializes all engine subsystems. Must be called before starting the 
  // game loop or using any subsystem functionality.
  void Initialize();

  // Starts the game loop.
  void Start();

  // Stops the game loop
  void Stop();

  // Terminates all engine subsystems. Must be called after the game loop is 
  // terminated. No more calls to subsystems are allowed beyond this point. 
  void Terminate();
};

} // namespace

#endif // ENGINE_ENGINE_H_