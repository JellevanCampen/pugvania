#include "graphics_glfw.h"
#include "engine.h"
#include "shader_resources.h"
#include "common\utility\debug_defines.h"

namespace engine {

VertexShader* GraphicsGLFW::LoadVertexShader(std::string filename)
{
  // TODO: use a resource manager here to share shaders among objects
  VertexShader* vertex_shader = new VertexShader(filename);
  vertex_shader->Load();
  return vertex_shader;
}

void GraphicsGLFW::UnloadVertexShader(VertexShader* vertex_shader)
{
  // TODO: use a resource manager here to share shaders among objects
  vertex_shader->Unload();
  delete vertex_shader;
}

FragmentShader* GraphicsGLFW::LoadFragmentShader(std::string filename)
{
  // TODO: use a resource manager here to share shaders among objects
  FragmentShader* fragment_shader = new FragmentShader(filename);
  fragment_shader->Load();
  return fragment_shader;
}

void GraphicsGLFW::UnloadFragmentShader(FragmentShader* fragment_shader)
{
  // TODO: use a resource manager here to share shaders among objects
  fragment_shader->Unload();
  delete fragment_shader;
}

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

void GraphicsGLFW::GLFWErrorCallback(int error, const char * description)
{
  g_log("GLFW Error: " + std::string(description), log::kError);
}

EngineSubsystem* GraphicsGLFW::Initialize()
{
  if (!glfwInit()) { g_log("Failed to initialize GLFW.", log::kError); }
  glfwSetErrorCallback(GLFWErrorCallback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  window = glfwCreateWindow(800, 450, "Pugvania Engine", NULL, NULL);
  if (!window) { g_log("Failed to create a window.", log::kError); }

  glfwMakeContextCurrent(window);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  int maj, min, rev;
  glfwGetVersion(&maj, &min, &rev);
  std::stringstream ss;
  ss << "Using OpenGL version: " << maj << "." << min << "." << rev;
  g_log(ss.str(), log::kEngine);

  glfwSwapInterval(1);

  // TODO: remove this, this is testing code
  VertexShader* shVert = LoadVertexShader("default");
  FragmentShader* shFrag = LoadFragmentShader("default");
  // remove this, this is testing code

  return this;
}

void GraphicsGLFW::Terminate()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

void GraphicsGLFW::Update()
{
  // Stop the engine if the window is closed
  if (glfwWindowShouldClose(window)) { g_engine->Stop(); }
}

void GraphicsGLFW::Draw()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
}

}; // namespace