#include "timing/timing.h"
#include "engine.h"
#include <sstream>
#include <iomanip>
#include "date.h"

namespace engine {

std::string Timing::GetTimestamp(bool include_date)
{
  std::ostringstream timestamp;
  if (include_date == true) {
    auto time = std::chrono::system_clock::now();
    date::operator<<(timestamp, time);
    timestamp << " | ";
  }
  unsigned long long days = MicrosToDays(total_time_micros_);
  unsigned long long hours = MicrosToHours(total_time_micros_, true);
  unsigned long long minutes = MicrosToMinutes(total_time_micros_, true);
  unsigned long long seconds = MicrosToSeconds(total_time_micros_, true);
  unsigned long long micros = total_time_micros_ % 1000000;
  if (days > 0) { timestamp << days << "d,"; }
  if (hours > 0) { timestamp << hours << "h,"; }
  if (minutes > 0) { timestamp << minutes << "m,"; }
  if (seconds > 0) { timestamp << seconds << "s:"; }
  timestamp << std::setw(6) << std::setfill('0') << micros;
  timestamp << " (upd:" << update_count_ << ",drw:" << draw_count_ << ")";
  return timestamp.str();
}

void Timing::Initialize() {
  LoadConfiguration();
}

void Timing::Terminate() {

}

void Timing::Update() {
  update_count_++;
  SampleUpdateRate();
}

void Timing::Draw() {
  draw_count_++;
  SampleDrawRate();
}

void Timing::LoadConfiguration() {
  ConfigFile engine_config((*g_engine->path)["config"] + "engine_config.ini", ConfigFile::WARN_COUT, ConfigFile::WARN_COUT);
  engine_config.ReadProperty<unsigned short int>("timing.update_rate_sample", &update_rate_sample_, 10);
  engine_config.ReadProperty<unsigned short int>("timing.draw_rate_sample", &draw_rate_sample_, 10);
  engine_config.ReadProperty<unsigned short int>("timing.rate_rolling_average_window", &rate_rolling_average_window_, 4);
}

void Timing::SampleUpdateRate() {
  if (update_count_ % update_rate_sample_ == 0) {
    TimePointMicros now = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros elapsed = (now - update_rate_sample_time_);
    update_rate_sample_time_ = now;
    float update_rate_current = update_rate_sample_ * 1000000.0f / ((float)elapsed.count());
    update_rate_ = (update_rate_ * (rate_rolling_average_window_ - 1) + (update_rate_current)) / rate_rolling_average_window_;
  }
}

void Timing::SampleDrawRate() {
  if (draw_count_ % draw_rate_sample_ == 0) {
    TimePointMicros now = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
    DurationMicros elapsed = (now - draw_rate_sample_time_);
    draw_rate_sample_time_ = now;
    float draw_rate_current = draw_rate_sample_ * 1000000.0f / ((float)elapsed.count());
    draw_rate_ = (draw_rate_ * (rate_rolling_average_window_ - 1) + (draw_rate_current)) / rate_rolling_average_window_;
  }
}

void Timing::PassStartSignal() {
  update_rate_sample_time_ = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
  draw_rate_sample_time_ = std::chrono::time_point_cast<DurationMicros>(std::chrono::high_resolution_clock::now());
}

void Timing::PassUpdateTimingInfo(unsigned long long delta_time_micros) {
  delta_time_micros_ = delta_time_micros;
  total_time_micros_ += delta_time_micros;
}

void Timing::PassDrawTimingInfo(float frame_interpolation) {
  frame_interpolation_ = frame_interpolation;
}

}; // namespace