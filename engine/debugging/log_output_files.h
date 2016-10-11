#pragma once
#ifndef ENGINE_DEBUGGING_LOGOUTPUTFILES_H_
#define ENGINE_DEBUGGING_LOGOUTPUTFILES_H_

#include "log_output.h"

namespace engine {

  // Log output that sends messages to individual files per channel. 
  class LogOutputFiles : public LogOutput {
  public:
    virtual void Initialize() override;
    virtual void Terminate() override;
    virtual void Log(const LogChannel& log_channel, std::string message) override;
  };

} // namespace

#endif // ENGINE_DEBUGGING_LOGOUTPUTFILES_H_