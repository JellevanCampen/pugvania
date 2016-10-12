#pragma once
#ifndef ENGINE_DEBUGGING_LOGOUTPUTTERMINAL_H_
#define ENGINE_DEBUGGING_LOGOUTPUTTERMINAL_H_

#include <unordered_map>
#include <string>
#include "log_output.h"
#include "engine_config.h"

#ifdef PF_WINDOWS 
#include "common\utility\windows_terminal_colors.h"
#endif // PF_WINDOWS

namespace engine {

// Log output that sends messages to the terminal. 
class LogOutputTerminal : public LogOutput {
 public:
  virtual void Initialize() override;
  virtual void Terminate() override;
  virtual void Log(const LogChannel& log_channel, std::string message) override;

 private:
#ifdef PF_WINDOWS 
   // Cache for Windows terminal color codes for the log channel colors. 
   std::unordered_map<std::string, WindowsTerminalColor> windows_log_color_cache_;
#endif // PF_WINDOWS
};

} // namespace

#endif // ENGINE_DEBUGGING_LOGOUTPUTTERMINAL_H_