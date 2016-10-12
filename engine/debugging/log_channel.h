#pragma once
#ifndef ENGINE_DEBUGGING_LOGCHANNEL_H_
#define ENGINE_DEBUGGING_LOGCHANNEL_H_

#include <string>
#include <forward_list>
#include "log_output.h"
#include "common\datatypes\color_types.h"

namespace engine {

// Represents a channel that accepts log messages and sends them to an 
// output channel. 
class LogChannel {
 public:
  LogChannel(std::string name, std::string tag, cRGBi color, bool timestamp = false)
      : name_(name), 
        tag_(tag), 
        color_(color),
        timestamp_(timestamp) {}

  void RegisterLogOutput(LogOutput* log_output);
  void Log(std::string message) const;

  const std::string name_;
  const std::string tag_;
  const cRGBi color_;
  const bool timestamp_{ false };

 private:
  // List of all output destinations this log channel should pipe messages to.
  std::forward_list<LogOutput*> log_outputs_;
};

} // namespace

#endif // ENGINE_DEBUGGING_LOGCHANNEL_H_