#pragma once
#ifndef ENGINE_DEBUGGING_LOGOUTPUTFILES_H_
#define ENGINE_DEBUGGING_LOGOUTPUTFILES_H_

#include <string>
#include <fstream>
#include <unordered_map>
#include "log_output.h"

namespace engine {

// Log output that sends messages to individual files per channel. 
class LogOutputFiles : public LogOutput {
  public:
    virtual void Initialize() override { };
  virtual void Terminate() override;
  virtual void Log(const LogChannel& log_channel, std::string message) override;

  private:
    std::unordered_map<std::string, std::fstream*> log_files_;
};

} // namespace

#endif // ENGINE_DEBUGGING_LOGOUTPUTFILES_H_