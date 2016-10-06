#pragma once
#ifndef ENGINE_DEBUGGING_LOGOUTPUT_H_
#define ENGINE_DEBUGGING_LOGOUTPUT_H_

#include <string>

namespace engine {

class LogChannel;

// Interface for log output destination. When plugged into Logging, log 
// messages can be sent to these outputs. 
class LogOutput {
 public:
  virtual ~LogOutput() {}
  virtual void Initialize() = 0;
  virtual void Terminate() = 0;
  virtual void Log(const LogChannel& log_channel, std::string message) = 0;
};

} // namespace

#endif // ENGINE_DEBUGGING_LOGOUTPUT_H_