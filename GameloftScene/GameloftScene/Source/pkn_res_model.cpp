#include "pkn_res_model.h"

namespace pugaknSDK {
  void ModelResourceFactory::Init()
  {
  }

  Resource * ModelResourceFactory::Load(std::string path, std::string extraPath)
  {
    ModelResource* res = new ModelResource();
    res->m_mesh.m_filename = ResourceManager::MODELS_PATH + path;
    res->m_mesh.Init();
    return res;
  }

  bool ModelResourceFactory::IsCompatible(std::string ext)
  {
    return ext == ".x";
  }
}

