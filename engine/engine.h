#pragma once
#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

#include <chrono>
#include <list>
#include <iostream>
#include "utility\game_time.h"
#include "utility\path.h"
#include "engine_subsystem.h"
#include "debugging\logging.h"

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
  Engine(Engine const&) = delete;
  void operator=(const Engine&) = delete;
  
  static void Create();
  static void Destroy();
  
  void Start();
  void Stop();

  const GameTime& GetGameTime() const { return game_time_; }
  float GetUpdateRate() const { return update_rate_; }
  float GetDrawRate() const { return draw_rate_; }

  // Pointers that give access to all engine subsystems. Safe to use after 
  // Create() was called and before Destroy() was called. 
  Path* path{ NULL };
  Logging* logging{ NULL };

 private:
  typedef std::chrono::duration<unsigned int, std::micro> DurationMicros;
  typedef std::chrono::time_point<std::chrono::high_resolution_clock, DurationMicros> TimePointMicros;

  // Allocates all Engine subsystems but does not perform initialization yet. 
  // Private constructor to ensure only a single Engine instance exists, 
  // following the singleton pattern. 
  Engine() { }
  ~Engine() { }
  void CreateSubsystems();
  void DestroySubsystems();
  void Initialize();
  void Terminate();

  void LoadEngineConfiguration();
  void RunGameLoop();
  void Update(unsigned int delta_time_micros);
  void Draw(float frame_interpolation);

  void SampleUpdateRate();
  void SampleDrawRate();

  std::list<EngineSubsystem*> subsystems_;

  bool is_running_{ false };
  GameTime game_time_{ };
  TimePointMicros update_rate_sample_time_;
  TimePointMicros draw_rate_sample_time_;
  float update_rate_{ 0.0f };
  float draw_rate_{ 0.0f };

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

  // Rate at which to sample update timings to determine the update rate. 
  unsigned short int update_rate_sample_{ 10 };
  // Rate at which to sample draw timings to determine the draw rate. 
  unsigned short int draw_rate_sample_{ 10 };
  // Size off the rolling average window used to smooth the update rate and 
  // draw rate measurements. A smaller window offers more precision but a 
  // higher amount of jitter. A larger window offers the opposite. 
  unsigned short int rate_rolling_average_window_{ 4 };
};

} // namespace

#endif // ENGINE_ENGINE_H_