#pragma once
#ifndef ENGINE_RESOURCES_RESOURCES_H_
#define ENGINE_RESOURCES_RESOURCES_H_

#include "engine_subsystem.h"
#include <unordered_map>

namespace engine {

// Keeps track of references to resources and frees them as needed.
class Resources : public EngineSubsystem {
public:

private:
  virtual std::string GetName() const override { return "Resources"; }
  virtual EngineSubsystem* Initialize() override;
  virtual void Terminate() override;
  virtual void Update() override;
  virtual void Draw() override;
};

} // namespace

#endif // ENGINE_RESOURCES_RESOURCES_H_
