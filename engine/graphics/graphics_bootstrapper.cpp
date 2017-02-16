#include "graphics_bootstrapper.h"
#include "engine.h"
#include "graphics_glfw.h"

namespace engine {

void GraphicsBootstrapper::CameraMove(Point2Df position)
{ 
  g_log("Calling bootstrapper function (graphics subsystem call before the graphics subsystem was bootstrapped): " __FUNCTION__, log::kError);
}

void GraphicsBootstrapper::Draw2DPoint(Point2Df point, float z, cRGBAf color) const
{
  g_log("Calling bootstrapper function (graphics subsystem call before the graphics subsystem was bootstrapped): " __FUNCTION__, log::kError);
}

void GraphicsBootstrapper::Draw2DLine(Line2Df line, float z, cRGBAf color) const
{
  g_log("Calling bootstrapper function (graphics subsystem call before the graphics subsystem was bootstrapped): " __FUNCTION__, log::kError);
}

void GraphicsBootstrapper::Draw2DRectangle(Rectangle2Df rectangle, float z, bool filled, cRGBAf color) const
{
  g_log("Calling bootstrapper function (graphics subsystem call before the graphics subsystem was bootstrapped): " __FUNCTION__, log::kError);
}

void GraphicsBootstrapper::Draw2DCircle(Circle2Df circle, float z, bool filled, cRGBAf color) const
{
  g_log("Calling bootstrapper function (graphics subsystem call before the graphics subsystem was bootstrapped): " __FUNCTION__, log::kError);
}

EngineSubsystem* GraphicsBootstrapper::Initialize()
{
  std::string graphics_subsystem;
  ConfigFile engine_config((*g_engine->path)["config"] + "engine_config.ini", ConfigFile::kWARN_COUT, ConfigFile::kWARN_COUT);
  engine_config.ReadProperty<std::string>("subsystems.graphics", &graphics_subsystem, "glfw");

  // Bootstrap a graphics subsystem implementation based on the config settings
  if (graphics_subsystem.compare("glfw") == 0) 
  { 
    Graphics* graphics = new GraphicsGLFW();
    g_engine->graphics = graphics;
    return graphics->Initialize();
  }
  
  g_log("The graphics subsystem specified in the config file was not recognized: " + graphics_subsystem, log::kError);
  return NULL;
}

void GraphicsBootstrapper::Terminate()
{
  g_log("Calling bootstrapper terminator (graphics subsystem bootcaller is terminated, meaning it failed to bootstrap the graphics subsystem during initialization): " __FUNCTION__, log::kError);
}

void GraphicsBootstrapper::Update()
{
  g_log("Calling bootstrapper function (graphics subsystem call before the graphics subsystem was bootstrapped): " __FUNCTION__, log::kError);
}

void GraphicsBootstrapper::Draw()
{
  g_log("Calling bootstrapper function (graphics subsystem call before the graphics subsystem was bootstrapped): " __FUNCTION__, log::kError);
}

}; // namespace