#pragma once
#ifndef ENGINE_RESOURCES_RESOURCE_H_
#define ENGINE_RESOURCES_RESOURCE_H_

#include <string>

namespace engine {

// Interface for a sharable resource. 
class Resource{
private:
  virtual void Load() = 0;
  virtual void Unload() = 0;
};

} // namespace

#endif // ENGINE_RESOURCES_RESOURCE_H_