#include "log_channel.h"
#include <iostream> // TODO(JELLE): Remove this import when LogOutput is fixed
#include "log_output.h"

namespace engine {

void LogChannel::RegisterLogOutput(LogOutput* log_output) {
  log_outputs_.push_front(log_output);
}

void LogChannel::Log(std::string message) const {
  for (LogOutput* out : log_outputs_)
    out->Log(*this, message);
}

} // namespace