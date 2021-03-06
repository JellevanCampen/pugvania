#pragma once
#ifndef ENGINE_ENGINESUBSYSTEM_H_
#define ENGINE_ENGINESUBSYSTEM_H_

#include <string>

namespace engine {

// Interface for subsystems of the engine. When plugged into the engine, 
// subsystems are automatically initialized, updated, drawn, and terminated. 
class EngineSubsystem {
 protected:
   virtual ~EngineSubsystem() { }

   virtual std::string GetName() const = 0;
   virtual EngineSubsystem* Initialize() = 0; // Returns the address of its initialized version (this can differ from its original address if bootstrapping was used).
   virtual void Terminate() = 0;
   virtual void Update() = 0;
   virtual void Draw() = 0;
   
  // Only the engine can manage initialization, updating, drawing, and 
  // termination of the subsystem as it performs initialization and 
  // termination, and it execution via the game loop. 
  friend class Engine;
};

} // namespace

#endif // ENGINE_ENGINESUBSYSTEM_H_