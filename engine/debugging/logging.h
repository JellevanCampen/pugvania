#pragma once
#ifndef ENGINE_DEBUGGING_LOGGING_H_
#define ENGINE_DEBUGGING_LOGGING_H_

#include <string>
#include <list>
#include "engine_subsystem.h"
#include "log_channel.h"
#include "log_output_terminal.h"

namespace engine {

// Manages the logging of messages. Messages can be sent to different 
// logging channels to categorize them. Logging channels subsequently pipe 
// incoming messages to an output channel including: the terminal, and log 
// files. 
class Logging : public EngineSubsystem{
 public:
  // The following constants are bit-masks for the various logging channels.
  static const unsigned int kLog_Default{ 0b00000000000000000000000000000001 };
  static const unsigned int kLog_Warning{ 0b00000000000000000000000000000010 };
  static const unsigned int kLog_Error{   0b00000000000000000000000000000100 };
  static const unsigned int kLog_Engine{  0b00000000000000000000000000001000 };

  virtual void Initialize() override;
  virtual void Terminate() override;
  virtual void Update() override { } // TODO(Jelle): Remove this, it is debug code to illustrate the logger
  virtual void Draw() override { } // TODO(Jelle): Remove this, it is debug code to illustrate the logger
  void Log(std::string message, unsigned int channels = Logging::kLog_Default);

 private:
   void InitializeLogOutputs();
   void InitializeLogChannels();
   void TerminateLogOutputs();

   LogOutputTerminal log_output_terminal_;
   std::list<LogOutput*> log_outputs_;
   std::list<LogChannel> log_channels_;
};

} // namespace

#endif // ENGINE_DEBUGGING_LOGGING_H_