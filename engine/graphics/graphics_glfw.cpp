#include "graphics_glfw.h"
#include "engine.h"
#include <GLFW\glfw3.h>
#include "common\utility\debug_defines.h"

namespace engine {

void GraphicsGLFW::CameraMove(Point2Df position)
{
  // TODO: implement function
  DEBUG_UNIMPLEMENTED
}

void GraphicsGLFW::Draw2DPoint(Point2Df point, float z, cRGBAf color) const
{
  // TODO: implement function
  DEBUG_UNIMPLEMENTED
}

void GraphicsGLFW::Draw2DLine(Line2Df line, float z, cRGBAf color) const
{
  // TODO: implement function
  DEBUG_UNIMPLEMENTED
}

void GraphicsGLFW::Draw2DRectangle(Rectangle2Df rectangle, float z, bool filled, cRGBAf color) const
{
  // TODO: implement function
  DEBUG_UNIMPLEMENTED
}

void GraphicsGLFW::Draw2DCircle(Circle2Df circle, float z, bool filled, cRGBAf color) const
{
  // TODO: implement function
  DEBUG_UNIMPLEMENTED
}

EngineSubsystem* GraphicsGLFW::Initialize()
{
  if (!glfwInit()) 
  {
    g_log("Failed to initialize GLFW.", log::kError);
  }

  return this;
}

void GraphicsGLFW::Terminate()
{
  glfwTerminate();
}

void GraphicsGLFW::Update()
{
  // TODO: implement function
  // DEBUG_UNIMPLEMENTED
}

void GraphicsGLFW::Draw()
{
  // TODO: implement function
  // DEBUG_UNIMPLEMENTED
}

}; // namespace