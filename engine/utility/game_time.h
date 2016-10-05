#pragma once
#ifndef ENGINE_UTILITY_GAMETIME_H_
#define ENGINE_UTILITY_GAMETIME_H_

namespace engine {

// Provides access to timing information on the game loop. This information is 
// updated on every update and draw call so that every object gets the same 
// timing information during a single update or frame. 
class GameTime {
 public:
  // Gets the time elapsed since the last update.
  unsigned int GetDeltaTimeMicros() const { return delta_time_micros_; }
  // Gets the time elapsed since the game loop was started.
  unsigned int GetTotalTimeMicros() const { return total_time_micros_; }
  // Gets the number of updates since the game loop was started.
  unsigned int GetUpdateCount() const { return update_count_; }
  // Gets the relative amount of time since the last update. A value of 0 
  // means the update just happened, and a value near 1 means the next update 
  // is imminent. 
  float GetFrameInterpolation() const { return frame_interpolation_; }
  // Gets the number of draws since the game loop was started.
  unsigned int GetDrawCount() const { return draw_count_; }

 private:
  // Updates the timing information for a new update. To be called by the 
  // game loop when an update happens.
  void Update(unsigned int delta_time_micros);
  // Updates the timing information for a new draw. To be called by the game 
  // loop when an update happens.
  void Draw(float frame_interpolation);

  unsigned int delta_time_micros_{ 0 };
  unsigned int total_time_micros_{ 0 };
  unsigned int update_count_{ 0 };
  float frame_interpolation_{ 0.0f };
  unsigned int draw_count_{ 0 };

  // The engine class is allowed to update the timing information as it 
  // possesses the game loop;
  friend class Engine;
};

} // namespace

#endif // ENGINE_UTILITY_GAMETIME_H_