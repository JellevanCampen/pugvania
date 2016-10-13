#include "timing/timing.h"
#include "engine.h"
#include <sstream>

namespace engine {

void Timing::Initialize() {
  LoadConfiguration();

  const void* adress = static_cast<const void*>(this);
  std::stringstream init_message;
  init_message << "Timing subsystem initialized at 0x" << adress;
  g_log(init_message.str(), log::kEngine);
}

void Timing::Terminate() {
  g_log("Timing subsystem terminating.", log::kEngine);
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

void Timing::LoadConfiguration() {
  ConfigFile engine_config((*g_engine->path)["config"] + "engine_config.ini", ConfigFile::WARN_COUT, ConfigFile::WARN_COUT);
  engine_config.ReadProperty<unsigned short int>("timing.update_rate_sample", &update_rate_sample_, 10);
  engine_config.ReadProperty<unsigned short int>("timing.draw_rate_sample", &draw_rate_sample_, 10);
  engine_config.ReadProperty<unsigned short int>("timing.rate_rolling_average_window", &rate_rolling_average_window_, 4);
}

}; // namespace