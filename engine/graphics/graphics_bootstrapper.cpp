#include "graphics_bootstrapper.h"
#include "engine.h"
#include "graphics_glfw.h"

namespace engine {

VertexShader* GraphicsBootstrapper::LoadVertexShader(std::string filename) { DEBUG_BOOTSTRAPPER_FUNCTION return NULL; }
void GraphicsBootstrapper::UnloadVertexShader(VertexShader* vertex_shader) { DEBUG_BOOTSTRAPPER_FUNCTION }
FragmentShader* GraphicsBootstrapper::LoadFragmentShader(std::string filename) { DEBUG_BOOTSTRAPPER_FUNCTION return NULL; }
void GraphicsBootstrapper::UnloadFragmentShader(FragmentShader* fragment_shader) { DEBUG_BOOTSTRAPPER_FUNCTION }
void GraphicsBootstrapper::CameraMove(Point2Df position) { DEBUG_BOOTSTRAPPER_FUNCTION }
void GraphicsBootstrapper::Draw2DPoint(Point2Df point, float z, cRGBAf color) const { DEBUG_BOOTSTRAPPER_FUNCTION }
void GraphicsBootstrapper::Draw2DLine(Line2Df line, float z, cRGBAf color) const { DEBUG_BOOTSTRAPPER_FUNCTION }
void GraphicsBootstrapper::Draw2DRectangle(Rectangle2Df rectangle, float z, bool filled, cRGBAf color) const { DEBUG_BOOTSTRAPPER_FUNCTION }
void GraphicsBootstrapper::Draw2DCircle(Circle2Df circle, float z, bool filled, cRGBAf color) const { DEBUG_BOOTSTRAPPER_FUNCTION }

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

void GraphicsBootstrapper::Terminate() { DEBUG_BOOTSTRAPPER_FUNCTION }
void GraphicsBootstrapper::Update() { DEBUG_BOOTSTRAPPER_FUNCTION }
void GraphicsBootstrapper::Draw() { DEBUG_BOOTSTRAPPER_FUNCTION }

}; // namespace