#include "timing/timing.h"

namespace engine {

void Timing::Initialize() {

}

void Timing::Terminate() {

}

void Timing::Update() {
  // Initialize the timers on the first update received. 
  if (!started_) {
    update_rate_sample_time_ = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    draw_rate_sample_time_ = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    started_ = true;
  }

  // TODO(Jelle): measure delta time in the Timing subsystem.
  // delta_time_micros_ = delta_time_micros;
  // total_time_micros_ += delta_time_micros;
  update_count_++;

  // Sample the update duration regularly to calculate the update rate. 
  if (update_count_ % update_rate_sample_ == 0) {
    TimePointMicros now = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros elapsed = (now - update_rate_sample_time_);
    update_rate_sample_time_ = now;
    float update_rate_current = update_rate_sample_ * 1000000.0f / ((float)elapsed.count());
    update_rate_ = (update_rate_ * (rate_rolling_average_window_ - 1) + (update_rate_current)) / rate_rolling_average_window_;
  }
}

void Timing::Draw() {
  // TODO(Jelle): measure frame interpolation in the Timing subsystem.
  // frame_interpolation_ = frame_interpolation;
  draw_count_++;

  // Sample the draw duration regularly to calculate the draw rate. 
  if (draw_count_ % draw_rate_sample_ == 0) {
    TimePointMicros now = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros elapsed = (now - draw_rate_sample_time_);
    draw_rate_sample_time_ = now;
    float draw_rate_current = draw_rate_sample_ * 1000000.0f / ((float)elapsed.count());
    draw_rate_ = (draw_rate_ * (rate_rolling_average_window_ - 1) + (draw_rate_current)) / rate_rolling_average_window_;
  }
}

}; // namespace