#pragma once
#ifndef ENGINE_RESOURCES_RESOURCE_CACHE_H_
#define ENGINE_RESOURCES_RESOURCE_CACHE_H_

#include "engine.h"
#include "resource.h"
#include "common/utility/debug_defines.h"
#include <unordered_map>

namespace engine {

// A resource along with its reference count. 
template<typename ResourceType>
struct CountedResource {
  ResourceType* resource_;
  int reference_count_ = 1;
};

// Cache that stores references to sharable resources.
template<typename ResourceType>
class Resource_Cache {
 public:
  bool ReserveResource(const std::string& resource_id, ResourceType* out_resource)
  {
    auto resource = resource_cache_.find(resource_id);
    if (resource == resource_cache_.end()) return false; // Resource was not found in cache
    resource->second.reference_count_++;
    out_resource = resource->second.resource_;
    return true; // Resource was found in cache
  }

  void StoreResource(const std::string& resource_id, ResourceType* resource)
  {
#ifdef SAFETY_CHECK
    if (resource == resource_cache_.count() != 0)
    {
      g_log("Tried to store a resource that is already present in the cache: " + resource_id, log::kWarning);
      return;
    }
#endif // SAFETY_CHECK
  }
    
  void FreeResource(const std::string& resource_id)
  {
    auto resource = resource_cache_.find(resource_id);
#ifdef SAFETY_CHECK
    if (resource == resource_cache_.end()) 
    {
      g_log("Tried to free a resource that is not present in the cache: " + resource_id, log::kWarning); 
      return;
    }
#endif // SAFETY_CHECK
    resource->second.reference_count_--;
    if (resource->second.reference_count_ <= 0)
    {
      resource->second.resource_.Unload();
      delete resource->second.resource_;
      resource_cache_.erase(resource);
    }
  }

 private:
  std::unordered_map<std::string, CountedResource<ResourceType>> resource_cache_;
};

} // namespace

#endif // ENGINE_RESOURCES_RESOURCE_CACHE_H_