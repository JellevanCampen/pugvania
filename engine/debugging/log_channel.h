#pragma once
#ifndef ENGINE_DEBUGGING_LOGCHANNEL_H_
#define ENGINE_DEBUGGING_LOGCHANNEL_H_

#include <string>

namespace engine {

// Represents a channel that accepts log messages and sends them to an 
// output channel. 
class LogChannel {
 public:
   LogChannel(std::string name, std::string tag, bool timestamp = false)
      : name_(name), 
        tag_(tag), 
        timestamp_(timestamp) {}

   void Log(std::string message);

 private:
  std::string name_;
  std::string tag_;
  bool timestamp_{ false };
};

} // namespace

#endif // ENGINE_DEBUGGING_LOGCHANNEL_H_