#pragma once
#ifndef ENGINE_GRAPHICS_SHADER_RESOURCES_H_
#define ENGINE_GRAPHICS_SHADER_RESOURCES_H_

#include "resources\resource.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>

namespace engine {

// A vertex shader, executed once per vertex.
class VertexShader : public Resource {
public:
  
 private:
  virtual void Load() override;
  virtual void Unload() override;

  std::string filename_;
  GLuint shader_id_{ NULL };
};

} // namespace

#endif // ENGINE_GRAPHICS_SHADER_RESOURCES_H_