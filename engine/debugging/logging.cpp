#include "logging.h"
#include "engine.h"
#include <sstream>

namespace engine {

void Logging::Initialize() {
  InitializeLogOutputs();
  InitializeLogChannels();
  
  const void* adress = static_cast<const void*>(this);
  std::stringstream init_message;
  init_message << "Logging subsystem initialized at 0x" << adress;
  Log(init_message.str(), log::kLog_Engine);
}

void Logging::Terminate() {
  Log("Logging subsystem terminated.", log::kLog_Engine);
  log_channels_.clear();
}

void Logging::Log(std::string message, LogID channels) {
  unsigned int mask = 0b1;
  for (LogChannel log : log_channels_) {
    if (channels & mask)
      log.Log(message);
    mask <<= 1;
  }
}

void Logging::InitializeLogOutputs() {
  log_outputs_.push_back(&log_output_terminal_);

  for (auto out : log_outputs_)
    out->Initialize();
}

void Logging::InitializeLogChannels() {
  // TODO(Jelle): Read the log channel configuration from file
  LogChannel ch_default("Default", "DFLT", false);
  ch_default.RegisterLogOutput(&log_output_terminal_);
  log_channels_.push_back(ch_default);
  LogChannel ch_warning("Warning", "WARN", true);
  ch_warning.RegisterLogOutput(&log_output_terminal_);
  log_channels_.push_back(ch_warning);
  LogChannel ch_error("Error", "ERRO", true);
  ch_error.RegisterLogOutput(&log_output_terminal_);
  log_channels_.push_back(ch_error);
  LogChannel ch_engine("Engine", "ENGI", false);
  ch_engine.RegisterLogOutput(&log_output_terminal_);
  log_channels_.push_back(ch_engine);
  LogChannel ch_game("Game", "GAME", false);
  ch_game.RegisterLogOutput(&log_output_terminal_);
  log_channels_.push_back(ch_game);
}

void Logging::TerminateLogOutputs() {
  for (auto out : log_outputs_)
    out->Terminate();
}

} // namespace