#include "game_time.h"

namespace engine {

void GameTime::Update(unsigned int delta_time_micros) {
  delta_time_micros_ = delta_time_micros;
  total_time_micros_ += delta_time_micros;
  update_count_++;
}

void GameTime::Draw(float frame_interpolation) {
  frame_interpolation_ = frame_interpolation;
  draw_count_++;
}

} // namespace