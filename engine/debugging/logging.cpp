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
  Log(init_message.str(), log::kEngine);
}

void Logging::Terminate() {
  Log("Logging subsystem terminating.", log::kEngine);
  TerminateLogOutputs();
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
  log_outputs_.push_back(&log_output_files_);
  log_outputs_.push_back(&log_output_globalfile_);

  for (auto out : log_outputs_)
    out->Initialize();
}

void Logging::InitializeLogChannels() {
  ConfigFile logging_config((*g_engine->path)["config"] + "logging_config.ini", ConfigFile::WARN_COUT, ConfigFile::WARN_COUT);
  InitializeLogChannel("default", logging_config);
  InitializeLogChannel("warning", logging_config);
  InitializeLogChannel("error", logging_config);
  InitializeLogChannel("engine", logging_config);
  InitializeLogChannel("game", logging_config);
}

void Logging::InitializeLogChannel(std::string channel, const ConfigFile & config_logging) {
  std::string name;
  std::string tag;
  bool timestamp;
  bool out_terminal;
  bool out_file;
  bool out_globalfile;

  config_logging.ReadProperty<std::string>(channel + ".name", &name, channel);
  config_logging.ReadProperty<std::string>(channel + ".tag", &tag, channel.substr(0, 4));
  config_logging.ReadProperty<bool>(channel + ".timestamp", &timestamp, false);
  config_logging.ReadProperty<bool>(channel + ".out_terminal", &out_terminal, true);
  config_logging.ReadProperty<bool>(channel + ".out_file", &out_file, true);
  config_logging.ReadProperty<bool>(channel + ".out_globalfile", &out_globalfile, true);

  LogChannel log_channel(name, tag, timestamp);
  if (out_terminal)
    log_channel.RegisterLogOutput(&log_output_terminal_);
  if (out_file)
    log_channel.RegisterLogOutput(&log_output_files_);
  if (out_globalfile)
    log_channel.RegisterLogOutput(&log_output_globalfile_);
  log_channels_.push_back(log_channel);
}

void Logging::TerminateLogOutputs() {
  for (auto out : log_outputs_)
    out->Terminate();
}

} // namespace