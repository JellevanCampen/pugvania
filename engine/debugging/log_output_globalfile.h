#pragma once
#ifndef ENGINE_DEBUGGING_LOGOUTPUTGLOBALFILE_H_
#define ENGINE_DEBUGGING_LOGOUTPUTGLOBALFILE_H_

#include "log_output.h"
#include <string>
#include <fstream>

namespace engine {

  // Log output that sends messages to individual files per channel. 
  class LogOutputGlobalFile : public LogOutput {
  public:
    virtual void Initialize() override;
    virtual void Terminate() override;
    virtual void Log(const LogChannel& log_channel, std::string message) override;

  private:
    std::ofstream log_file_;
  };

} // namespace

#endif // ENGINE_DEBUGGING_LOGOUTPUTGLOBALFILE_H_