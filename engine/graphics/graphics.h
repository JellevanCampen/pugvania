#pragma once
#ifndef ENGINE_GRAPHICS_GRAPHICS_H_
#define ENGINE_GRAPHICS_GRAPHICS_H_

#include "engine_subsystem.h"
#include "common\datatypes\color_types.h"

namespace engine {

// TODO(Jelle): remove these once they have been implemented. 
struct Line2Df;
struct Rectangle2Df;
struct Circle2Df;

// Interface for graphics subsystems. 
class Graphics : EngineSubsystem{
 public:
  virtual void Draw2DLine(Line2Df line, float z = 0.0f, cRGBAf color = cRGBAf()) const = 0;
  virtual void Draw2DLine(float x1, float y1, float x2, float y2, float z = 0.0f, cRGBAf color = cRGBAf()) const = 0;
  virtual void Draw2DRectangle(Rectangle2Df rectangle, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const = 0;
  virtual void Draw2DRectangle(float x1, float y1, float x2, float y2, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const = 0;
  virtual void Draw2DCircle(Circle2Df circle, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const = 0;
  virtual void Draw2DCircle(float x, float y, float r, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const = 0;

 protected:
  virtual ~Graphics() { }

  virtual std::string GetName() const = 0;
  virtual void Initialize() = 0;
  virtual void Terminate() = 0;
  virtual void Update() = 0;
  virtual void Draw() = 0;
};

} // namespace

#endif // ENGINE_GRAPHICS_GRAPHICS_H_