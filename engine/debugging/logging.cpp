#include "logging.h"

namespace engine {

void Logging::Initialize() {
  InitializeLogOutputs();
  InitializeLogChannels();
  Log("Logging subsystem initialized.", kLog_Engine);
}

void Logging::Terminate() {
  Log("Logging subsystem terminated.", kLog_Engine);
  log_channels_.clear();
}

void Logging::Log(std::string message, unsigned int channels) {
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
  LogChannel ch_engine("Engine", "ENGI", true);
  ch_engine.RegisterLogOutput(&log_output_terminal_);
  log_channels_.push_back(ch_engine);
}

void Logging::TerminateLogOutputs() {
  for (auto out : log_outputs_)
    out->Terminate();
}

} // namespace