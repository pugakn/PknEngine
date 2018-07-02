#include "pkn_res_shader.h"
#include <fstream>
#include <string>
#include <sstream> 
namespace pugaknSDK {
  void ShaderResourceFactory::Init()
  {
  }
  Resource * ShaderResourceFactory::Load(std::string path)
  {
    ShaderResource* res = new ShaderResource();
    std::stringstream buffer_vs;
    std::stringstream buffer_fs;

    std::ifstream file_vs(path);
    buffer_vs << file_vs.rdbuf();
    res->m_source = buffer_vs.str();

    std::ifstream file_fs("fs_quad.glsl");
    buffer_fs << file_fs.rdbuf();
    std::string fsource = buffer_fs.str();

    res->m_shader.CreateFromMemory(res->m_source,fsource);
    return res;
  }
  bool ShaderResourceFactory::IsCompatible(std::string ext)
  {
    return ext == ".glsl";
  }
}