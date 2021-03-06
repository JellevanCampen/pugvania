#include "log_output_globalfile.h"
#include <sstream>
#include "log_channel.h"
#include "engine.h"

namespace engine {

void LogOutputGlobalFile::Initialize() {
  log_file_.open((*g_engine->path)["logging"] + "_global.log", std::ios::out | std::ios::app);
  // TODO(Jelle): Print the correct time stamp once it's retrievable in the 
  // engine
  log_file_ << "----START:[" << g_engine->timing->GetTimestamp(true) << "]" << std::endl;
}

void LogOutputGlobalFile::Terminate() {
  // TODO(Jelle): Print the correct time stamp once it's retrievable in the 
  // engine
  log_file_ << "----END:[" << g_engine->timing->GetTimestamp(true) << "]" << std::endl;
  log_file_.close();
}

void LogOutputGlobalFile::Log(const LogChannel& log_channel, std::string message) {
  std::stringstream log_message;
  if (log_channel.timestamp_ == true)
    log_message << "[" << g_engine->timing->GetTimestamp() << "] ";
  log_message << log_channel.tag_ << ": ";
  log_message << message;
  log_file_ << log_message.str() << std::endl;
}

} // namespace
