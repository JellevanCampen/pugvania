#include "log_channel.h"
#include <iostream> // TODO(JELLE): Remove this import when LogOutput is fixed
#include "log_output.h"

namespace engine {

void LogChannel::Log(std::string message) const {
  // TODO(JELLE): Fix this when LogOutput is fixed
  //for (LogOutput* out : log_outputs_)
  //  out->Log(*this, message);
  std::string m;
  if (timestamp_) { m += "[TIME_STAMP] "; }
  m += tag_ + " >> " + message;
  std::cout << m << std::endl;
}

} // namespace