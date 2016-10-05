#pragma once
#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

#include <chrono>
#include "utility\game_time.h"

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

 private:
  // Runs the game loop using the specified settings.
  void RunGameLoop();
  // Updates the game world. Sends requests to all subsystems and game objects 
  // to update themselves. 
  void Update(unsigned int delta_time_micros);
  // Draws the game world. Sends requests to all subsystems and game objects 
  // to draw themselves.
  void Draw(float frame_interpolation);

  bool is_running_{ false };
  GameTime game_time_{ };
  // Whether or not output should be drawn on screen. Can be disabled to speed 
  // up simulations by only performing updates. 
  bool drawing_is_enabled_{ true };
  // Whether updates should be performed at fixed time steps or as fast as 
  // possible. A fixed time step improves stability by making updates 
  // deterministic while a variable time step can offer a smoother experience 
  // on faster systems. (See: R. Nystrom - Game Programming Patterns pages 
  // 123 to 137 for more info.)
  bool update_time_step_is_fixed_{ false };
  // Update interval to use in case of a fixed update time step. 
  unsigned int time_step_micros_{ 1000000 / 60 };
  // Whether output should be drawn on screen as fast as possible, or only 
  // once per update. By using the frame interpolation value provided on draw 
  // calls, it is possible to draw animations at a higher rate then the 
  // update rate. 
  bool draw_rate_is_capped_{ false };
  // The maximum of draws to drop before forcedly rendering one, in case the 
  // update + draw time is longer than the desired fixed update rate. 
  unsigned short int max_frame_skip_{ 5 };

};

} // namespace

#endif // ENGINE_ENGINE_H_