#pragma once
#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

#include <chrono>
#include <list>
#include <iostream>
#include "engine_subsystem.h"
#include "common/utility/path.h"
#include "debugging/logging.h"
#include "timing/timing.h"

namespace engine {

// Global pointer to the engine. Safe to use after Create() is called and 
// before Destroy() is called. (Implementation note: the variable is declared 
// in the source file to avoid multiple definitions when including the 
// engine.h header in other files.)  
extern Engine* g_engine;

// Global log function. Safe to use after Create() is called and before 
// Destroy() is called.
void g_log(std::string message, LogID channels = log::kDefault);

// Manages the game loop and all subsystems used to run the Game. 
class Engine {
 public:  
  static void Create();
  static void Destroy();
  
  void Start();
  void Stop();

  // Pointers that give access to all engine subsystems. Safe to use after 
  // Create() was called and before Destroy() was called. 
  Path* path{ NULL };
  Logging* logging{ NULL };
  Timing* timing{ NULL };

 private:
  typedef std::chrono::duration<unsigned int, std::micro> DurationMicros;
  typedef std::chrono::time_point<std::chrono::high_resolution_clock, DurationMicros> TimePointMicros;

  // Private constructor to ensure only a single Engine instance.
  Engine() { }
  ~Engine() { }
  Engine(Engine const&) = delete;
  void operator=(const Engine&) = delete;

  void CreateSubsystems();
  void DestroySubsystems();
  void Initialize();
  void Terminate();
  void LogInitializationMessage(EngineSubsystem* subsystem);
  void LogTerminationMessage(EngineSubsystem* subsystem);

  void LoadConfiguration();
  void RunGameLoop();
  void Update(unsigned int delta_time_micros);
  void Draw(float frame_interpolation);

  std::list<EngineSubsystem*> subsystems_;

  bool is_running_{ false };
  bool logger_initialized_{ false };

  // Whether or not output should be drawn on screen. Can be disabled to speed 
  // up simulations by only performing updates. 
  bool drawing_is_enabled_{ true };
  // Whether updates should be performed at fixed time steps or as fast as 
  // possible. A fixed time step improves stability by making updates 
  // deterministic while a variable time step can offer a smoother experience 
  // on faster systems. (See: R. Nystrom - Game Programming Patterns pages 
  // 123 to 137 for more info.)
  bool update_time_step_is_fixed_{ true };
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