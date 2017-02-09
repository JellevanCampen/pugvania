#pragma once
#ifndef ENGINE_TIMING_TIMING_H_
#define ENGINE_TIMING_TIMING_H_

#include <chrono>
#include <string>
#include "engine_subsystem.h"

namespace engine {

// Keeps information on the timing of the game loop.
class Timing : public EngineSubsystem {
 public: 
  unsigned long long GetDeltaTimeMicros() const { return delta_time_micros_; }
  unsigned long long GetTotalTimeMicros() const { return total_time_micros_; }
  unsigned long long GetUpdateCount() const { return update_count_; }
  unsigned long long GetDrawCount() const { return draw_count_; }
  float GetFrameInterpolation() const { return frame_interpolation_; }
  float GetUpdateRate() const { return update_rate_; }
  float GetDrawRate() const { return draw_rate_; }
  std::string GetTimestamp(bool include_date = false);

  static unsigned long long MicrosToDays(unsigned long long micros) { return micros / (1000000llu * 60 * 60 * 24); }
  static unsigned long long MicrosToHours(unsigned long long micros, bool modulus = false) { return modulus ? (micros / (1000000llu * 60 * 60)) % 24 : micros / (1000000llu * 60 * 60); }
  static unsigned long long MicrosToMinutes(unsigned long long micros, bool modulus = false) { return modulus ? (micros / (1000000llu * 60)) % 60 : micros / (1000000llu * 60); }
  static unsigned long long MicrosToSeconds(unsigned long long micros, bool modulus = false) { return modulus ? (micros / 1000000llu) % 60 : micros / 1000000llu; }

 private:
  typedef std::chrono::duration<unsigned long long, std::micro> DurationMicros;
  typedef std::chrono::time_point<std::chrono::high_resolution_clock, DurationMicros> TimePointMicros;

  virtual std::string GetName() const override { return "Timing"; }
  virtual void Initialize() override;
  virtual void Terminate() override;
  virtual void Update() override;
  virtual void Draw() override;

  void LoadConfiguration();

  void SampleUpdateRate();
  void SampleDrawRate();

  // Hook into the game loop to retrieve specific timing info. 
  void PassStartSignal();
  void PassUpdateTimingInfo(unsigned long long delta_time_micros);
  void PassDrawTimingInfo(float frame_interpolation);

  unsigned long long delta_time_micros_{ 0 };
  unsigned long long total_time_micros_{ 0 };
  unsigned long long update_count_{ 0 };
  unsigned long long draw_count_{ 0 };
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
