#pragma once
#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

#include <chrono>
#include <list>
#include <iostream>
#include "utility\game_time.h"
#include "engine_subsystem.h"
#include "debugging\logging.h"

namespace engine {

// Global reference to the Engine to make it more easily available. The 
// variable is declared in the source file to avoid multiple definitions when 
// including the engine.h header in other files. 
extern Engine* g_engine;

// The log function is made globally avaiable for ease of logging. 
void g_log(std::string message, LogID channels = log::kDefault);

// Encompasses all subsystems used to run the Game. It is responsible for 
// subsystem initialization and termination, as well as running the game loop.
class Engine {
 public:
  // Instantiates (if necessary) the Engine singleton and returns is. Note 
  // that this is the safest way to access the Engine, at is guaranteed to be 
  // constructed. For easier access, a pointer to the access is stored 
  // globally in the engine:: namespace. Thus, making safe access: 
  // 'engine::Engine::Get()' and unsafe access: 'engine::engine'. 
  static Engine* get();

  // Disallow use of the copy and assignment constructors to prevent creating 
  // multiple instances of the engine, following the singleton pattern. 
  Engine(Engine const&) = delete;
  void operator=(Engine const&) = delete;
  // Frees all Engine subsystems after termination was performed.
  ~Engine();
  // Starts the game loop.
  void Start();
  // Stops the game loop
  void Stop();
  const GameTime& GetGameTime() const { return game_time_; }
  float GetUpdateRate() const { return update_rate_; }
  float GetDrawRate() const { return draw_rate_; }

  // Unsafe access to all subsystems of the engine. These pointers are only 
  // set when the submodules are initialized. The pointers are available to 
  // provide shorthand access to subsystems in the engine namespace: 
  // e.g. engine->logging 
  Logging* logging{ NULL };

 private:
  typedef std::chrono::duration<unsigned int, std::micro> DurationMicros;
  typedef std::chrono::time_point<std::chrono::high_resolution_clock, DurationMicros> TimePointMicros;

  // Allocates all Engine subsystems but does not perform initialization yet. 
  // Private constructor to ensure only a single Engine instance exists, 
  // following the singleton pattern. 
  Engine();
  // Initializes all engine subsystems. Automatically called at construction 
  // to assure all subsystems are initialized before the game loop is started.
  void Initialize();
  // Terminates all engine subsystems. Automatically called at deconstruction. 
  void Terminate();

  // Rate at which to sample update timings to determine the update rate. 
  static const unsigned short int update_rate_sample_ = 10;
  // Rate at which to sample draw timings to determine the draw rate. 
  static const unsigned short int draw_rate_sample_ = 10;
  // Size off the rolling average window used to smooth the update rate and 
  // draw rate measurements. A smaller window offers more precision but a 
  // higher amount of jitter. A larger window offers the opposite. 
  static const unsigned short int rate_rolling_average_window = 4;

  // Runs the game loop using the specified settings.
  void RunGameLoop();
  // Updates the game world. Sends requests to all subsystems and game objects 
  // to update themselves. 
  void Update(unsigned int delta_time_micros);
  // Draws the game world. Sends requests to all subsystems and game objects 
  // to draw themselves.
  void Draw(float frame_interpolation);
  void SampleUpdateRate();
  void SampleDrawRate();

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
  // Holds the time of the last sampled update.
  TimePointMicros update_rate_sample_time_;
  // Holds the time of the last sampled draw.
  TimePointMicros draw_rate_sample_time_;
  float update_rate_{ 0.0f };
  float draw_rate_{ 0.0f };

  // List of active engine subsystems. All subsystems in this list are 
  // automatically initializes, updated, drawn, and terminated. (A list 
  // is used as random access is not required, only forward and backward 
  // iteration.) 
  //
  // In regard to memory management: the constructor of the Engine class 
  // allocated all subsystems and the destructor of the Engine class takes 
  // care of freeing the memory.
  std::list<EngineSubsystem*> subsystems_;

  Logging* subsystem_logging_{ NULL };
};

} // namespace

#endif // ENGINE_ENGINE_H_