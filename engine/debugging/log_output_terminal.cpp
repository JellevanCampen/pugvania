#include "log_output_terminal.h"
#include <iostream>
#include <string>
#include "log_channel.h"
#include "engine.h"

#ifdef PF_WINDOWS 
#include <Windows.h>
#endif // PF_WINDOWS

namespace engine {

void LogOutputTerminal::Initialize() {

}

void LogOutputTerminal::Terminate() {

}

void LogOutputTerminal::Log(const LogChannel& log_channel, std::string message) {
#ifdef PF_WINDOWS 
  WindowsTerminalColor color_code;
  // Lazy calculation of the log channel color's Windows terminal color code.
  if (windows_log_color_cache_.count(log_channel.tag_) == 0) {
    color_code = WindowsTerminalColorUtility::GetClosestWindowsTerminalColor(cRGBi(log_channel.color_));
    windows_log_color_cache_.emplace(log_channel.tag_, color_code);
  }
  else {
    color_code = windows_log_color_cache_.at(log_channel.tag_);
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), int(color_code));
#endif // PF_WINDOWS
  std::string m;
  if (log_channel.timestamp_) { m += "[" + g_engine->timing->GetTimestamp() + "] "; }
  m += log_channel.tag_ + ": " + message;
  std::cout << m << std::endl;
}

} // namespace
