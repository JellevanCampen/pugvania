#pragma once
#ifndef ENGINE_GRAPHICS_GRAPHICS_GLFW_H_
#define ENGINE_GRAPHICS_GRAPHICS_GLFW_H_

#include "graphics.h"

namespace engine {

// Interface for graphics subsystems. 
class GraphicsGLFW : public Graphics {
public:
  // Camera operations
  virtual void CameraMove(Point2Df position) override;
  // Primitive drawing
  virtual void Draw2DPoint(Point2Df point, float z, cRGBAf color) const override;
  virtual void Draw2DLine(Line2Df line, float z = 0.0f, cRGBAf color = cRGBAf()) const override;
  virtual void Draw2DRectangle(Rectangle2Df rectangle, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const override;
  virtual void Draw2DCircle(Circle2Df circle, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const override;

private:
  std::string GetName() const override { return "Graphics(GLFW)"; }
  virtual void Initialize() override;
  virtual void Terminate() override;
  virtual void Update() override;
  virtual void Draw() override;
};

} // namespace

#endif // ENGINE_GRAPHICS_GRAPHICS_GLFW_H_