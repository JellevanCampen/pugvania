#include "shader_resources.h"
#include "common\utility\debug_defines.h"
#include <fstream>
#include <vector>

namespace engine {

bool ShaderUtility::ReadAndCompile(std::string filename, GLuint shader_id)
{
  // Read the shader code from file
  std::string shader_code;
  std::ifstream shader_code_stream((*g_engine->path)["shaders"] + filename, std::ios::in);
  if (!shader_code_stream.is_open())
  {
    g_log("Failed to open shader file: " + (*g_engine->path)["shaders"] + filename, log::kWarning);
    return false;
  }
  std::string read = "";
  while (std::getline(shader_code_stream, read))
    shader_code += "\n" + read;
  shader_code_stream.close();

  // Compile the shader
  char const * shader_code_pointer = shader_code.c_str();
  glShaderSource(shader_id, 1, &shader_code_pointer, NULL);
  glCompileShader(shader_id);

#ifdef SAFETY_CHECK
  GLint compile_status;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == GL_FALSE)
  {
    int info_log_length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    std::vector<char> shader_info_log(info_log_length);
    glGetShaderInfoLog(shader_id, info_log_length, NULL, &shader_info_log[0]);
    g_log("Failed to compile shader (" + filename + "): " + std::string(&shader_info_log[0]), log::kWarning);
    return false;
  }
#endif //SAFETY_CHECK

  return true;
}

void VertexShader::Load()
{  
  shader_id_ = glCreateShader(GL_VERTEX_SHADER);
  ShaderUtility::ReadAndCompile(filename_ + ".vs", shader_id_);
}

void VertexShader::Unload()
{
  glDeleteShader(shader_id_);
}

void FragmentShader::Load()
{
  shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
  ShaderUtility::ReadAndCompile(filename_ + ".fs", shader_id_);
}

void FragmentShader::Unload()
{
  glDeleteShader(shader_id_);
}

}; // namespace