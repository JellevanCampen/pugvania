#include "log_output_files.h"
#include <sstream>
#include "log_channel.h"
#include "engine.h"

namespace engine {

void LogOutputFiles::Terminate() {
  for (auto log_file : log_files_) {
    *log_file.second << "----END:[TIME_STAMP]" << std::endl;
    log_file.second->close();
    delete log_file.second;
  }
  log_files_.clear();
}

void LogOutputFiles::Log(const LogChannel& log_channel, std::string message) {
  std::fstream* log_file{ NULL };

  // Lazy instantiation of the file streams
  if (log_files_.count(log_channel.tag_) == 0) {
    log_file = new std::fstream;
    log_file->open((*g_engine->path)["logging"] + log_channel.name_ + ".log", std::ios::out | std::ios::app);
    // TODO(Jelle): Print the correct time stamp once it's retrievable in the 
    // engine
    *log_file << "----START:[TIME_STAMP]" << std::endl;
    log_files_.emplace(log_channel.tag_, log_file);
  } else {
    log_file = log_files_.at(log_channel.tag_);
  }

  std::stringstream log_message;
  // TODO(Jelle): Print the correct time stamp once it's retrievable in the 
  // engine
  if (log_channel.timestamp_ == true)
    log_message << "[TIME_STAMP] ";
  log_message << message;
  *log_file << log_message.str() << std::endl;
}

} // namespace
