#pragma once
#ifndef ENGINE_GRAPHICS_GRAPHICS_H_
#define ENGINE_GRAPHICS_GRAPHICS_H_

#include "engine_subsystem.h"
#include "common\datatypes\color_types.h"
#include "common\datatypes\shape_types.h"

namespace engine {

// Interface for graphics subsystems. 
class Graphics : EngineSubsystem{
 public:
  // Camera operations
   virtual void CameraMove(Point2Df position) = 0;
  // Primitive drawing
  virtual void Draw2DPoint(Point2Df point, float z = 0.0f, cRGBAf color = cRGBAf()) const = 0;
  virtual void Draw2DLine(Line2Df line, float z = 0.0f, cRGBAf color = cRGBAf()) const = 0;
  virtual void Draw2DRectangle(Rectangle2Df rectangle, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const = 0;
  virtual void Draw2DCircle(Circle2Df circle, float z = 0.0f, bool filled = false, cRGBAf color = cRGBAf()) const = 0;

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