#pragma once
#ifndef ENGINE_GRAPHICS_GRAPHICS_GLFW_H_
#define ENGINE_GRAPHICS_GRAPHICS_GLFW_H_

#include "graphics.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace engine {

// Graphics subsystem implementation using GLFW. Renders graphics onscreen.
class GraphicsGLFW : public Graphics {
public:
  // Shader operations
  virtual VertexShader* LoadVertexShader(std::string filename) override;
  virtual void UnloadVertexShader(VertexShader* vertex_shader) override;
  virtual FragmentShader* LoadFragmentShader(std::string filename) override;
  virtual void UnloadFragmentShader(FragmentShader* fragment_shader) override;
  // Camera operations
  virtual void CameraMove(Point2Df position) override;
  // Primitive drawing
  virtual void Draw2DPoint(Point2Df point, float z, cRGBAf color) const override;
  virtual void Draw2DLine(Line2Df line, float z = 0.0f, cRGBAf color = cRGBAf()) const override;
  virtual void Draw2DRectangle(Rectangle2Df rectangle, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const override;
  virtual void Draw2DCircle(Circle2Df circle, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const override;
  static void GLFWErrorCallback(int error, const char* description);

private:
  std::string GetName() const override { return "Graphics(GLFW)"; }
  virtual EngineSubsystem* Initialize() override;
  virtual void Terminate() override;
  virtual void Update() override;
  virtual void Draw() override;

  GLFWwindow* window;
};

} // namespace

#endif // ENGINE_GRAPHICS_GRAPHICS_GLFW_H_