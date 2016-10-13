#pragma once
#ifndef ENGINE_DEBUGGING_LOGGING_H_
#define ENGINE_DEBUGGING_LOGGING_H_

#include <string>
#include <list>
#include "engine_subsystem.h"
#include "common/utility/config_file.h"
#include "log_channel.h"
#include "log_output_terminal.h"
#include "log_output_files.h"
#include "log_output_globalfile.h"

namespace engine {

typedef unsigned int LogID;

namespace log {
  // The following constants are bit-masks for the various logging channels.
  static const LogID kDefault{ 0b00000000000000000000000000000001 };
  static const LogID kWarning{ 0b00000000000000000000000000000010 };
  static const LogID kError{   0b00000000000000000000000000000100 };
  static const LogID kEngine{  0b00000000000000000000000000001000 };
  static const LogID kGame{    0b00000000000000000000000000010000 };
}

// Manages the logging of messages. Messages can be sent to different 
// logging channels to categorize them. Logging channels subsequently pipe 
// incoming messages to an output channel including: the terminal, and log 
// files. 
class Logging : public EngineSubsystem{
 public:
  void Log(std::string message, LogID channels = log::kDefault);

 private:
   virtual std::string GetName() const { return "Logging"; }
   virtual void Initialize() override;
   virtual void Terminate() override;
   virtual void Update() override { }
   virtual void Draw() override { }

   void InitializeLogOutputs();
   void InitializeLogChannels();
   void InitializeLogChannel(std::string channel, const ConfigFile& config_logging);
   void TerminateLogOutputs();

   LogOutputTerminal log_output_terminal_;
   LogOutputFiles log_output_files_;
   LogOutputGlobalFile log_output_globalfile_;
   std::list<LogOutput*> log_outputs_;
   std::list<LogChannel> log_channels_;
};

} // namespace

#endif // ENGINE_DEBUGGING_LOGGING_H_