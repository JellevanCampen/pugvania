#pragma once
#ifndef ENGINE_GRAPHICS_SHADER_RESOURCES_H_
#define ENGINE_GRAPHICS_SHADER_RESOURCES_H_

#include "resources\resource.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>

namespace engine {

// Utility functions for shaders
class ShaderUtility {
 private:
  static bool ReadAndCompile(std::string filename, GLuint shader_id);

  friend class VertexShader;
  friend class FragmentShader;
};

// A vertex shader, executed once per vertex.
class VertexShader : public Resource {
public:
  VertexShader(std::string filename) : filename_(filename) { }

 private:
  virtual void Load() override;
  virtual void Unload() override; 

  std::string filename_;
  GLuint shader_id_{ NULL };

  // TODO: replace this, as the resource cache should be in charge of loading and unloading
  friend class GraphicsGLFW;
};

// A fragment shader, executed once per fragment.
class FragmentShader : public Resource {
public:
  FragmentShader(std::string filename) : filename_(filename) { }

private:
  virtual void Load() override;
  virtual void Unload() override;

  std::string filename_;
  GLuint shader_id_{ NULL };

  // TODO: replace this, as the resource cache should be in charge of loading and unloading
  friend class GraphicsGLFW;
};

} // namespace

#endif // ENGINE_GRAPHICS_SHADER_RESOURCES_H_