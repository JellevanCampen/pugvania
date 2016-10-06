#include "logging.h"

namespace engine {

void Logging::Initialize() {
  // TODO(Jelle): Read the log channel configuration from file
  // Note that these are added in reverse order because forward_list doesn't 
  // implement a push_back function!
  log_channels_.push_front(LogChannel("Engine", "ENGI", true));
  log_channels_.push_front(LogChannel("Error", "ERRO", true));
  log_channels_.push_front(LogChannel("Warning", "WARN", true));
  log_channels_.push_front(LogChannel("Default", "DFLT", false));

  Log("Logging subsystem initialized.", kLog_Engine);
}

void Logging::Terminate() {
  Log("Logging subsystem terminated.", kLog_Engine);

  log_channels_.clear();
}

void Logging::Log(std::string message, unsigned int channels) {
  unsigned int mask = 0b1;
  for (LogChannel log : log_channels_) {
    if (channels & mask)
      log.Log(message);
    mask <<= 1;
  }
}

} // namespace