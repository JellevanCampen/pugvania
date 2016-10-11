#include "log_output_terminal.h"
#include <iostream>
#include <string>
#include "log_channel.h"

namespace engine {

void LogOutputTerminal::Initialize() {

}

void LogOutputTerminal::Terminate() {

}

void LogOutputTerminal::Log(const LogChannel& log_channel, std::string message) {
  std::string m;
  // TODO(Jelle): Print the correct time stamp once it's retrievable in the 
  // engine
  if (log_channel.timestamp_) { m += "[TIME_STAMP] "; }
  m += log_channel.tag_ + ": " + message;
  std::cout << m << std::endl;
}

} // namespace
