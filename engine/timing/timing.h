#pragma once
#ifndef ENGINE_TIMING_TIMING_H_
#define ENGINE_TIMING_TIMING_H_

#include <chrono>
#include "engine_subsystem.h"

namespace engine {

// Keeps information on the timing of the game loop.
class Timing : public EngineSubsystem {
 public: 
  virtual std::string GetName() const { return "Timing"; }
  virtual void Initialize() override;
  virtual void Terminate() override;
  virtual void Update() override;
  virtual void Draw() override;

  unsigned int GetDeltaTimeMicros() const { return delta_time_micros_; }
  unsigned int GetTotalTimeMicros() const { return total_time_micros_; }
  unsigned int GetUpdateCount() const { return update_count_; }
  unsigned int GetDrawCount() const { return draw_count_; }
  float GetFrameInterpolation() const { return frame_interpolation_; }

  float GetUpdateRate() const { return update_rate_; }
  float GetDrawRate() const { return draw_rate_; }

 private:
  typedef std::chrono::duration<unsigned int, std::micro> DurationMicros;
  typedef std::chrono::time_point<std::chrono::high_resolution_clock, DurationMicros> TimePointMicros;

  void LoadConfiguration();

  void SampleUpdateRate();
  void SampleDrawRate();

  // Hook into the game loop to retrieve specific timing info. 
  void PassStartSignal();
  void PassUpdateTimingInfo(unsigned int delta_time_micros);
  void PassDrawTimingInfo(float frame_interpolation);

  unsigned int delta_time_micros_{ 0 };
  unsigned int total_time_micros_{ 0 };
  unsigned int update_count_{ 0 };
  unsigned int draw_count_{ 0 };
  float frame_interpolation_{ 0.0f };

  TimePointMicros update_rate_sample_time_;
  TimePointMicros draw_rate_sample_time_;
  float update_rate_{ 0.0f };
  float draw_rate_{ 0.0f };

  // Rate at which to sample update timings to determine the update rate. 
  unsigned short int update_rate_sample_{ 10 };
  // Rate at which to sample draw timings to determine the draw rate. 
  unsigned short int draw_rate_sample_{ 10 };
  // Size off the rolling average window to smooth the update and draw rates.
  unsigned short int rate_rolling_average_window_{ 4 };

  // The engine passes timing info via Pass{Update|Draw}TimingInfo().
  friend class Engine;
};

} // namespace

#endif // ENGINE_TIMING_TIMING_H_
