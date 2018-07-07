#include "pkn_resource_manager.h"
#include <iostream>

#include "pkn_res_shader.h"
#include "pkn_res_texture.h"
#include "pkn_res_model.h"
namespace pugaknSDK {
  void ResourceManager::Init()
  {
    Instance().m_foctories.push_back(std::move(std::make_unique<ShaderResourceFactory>()));
    Instance().m_foctories.push_back(std::move(std::make_unique<TextureResourceFactory>()));
    Instance().m_foctories.push_back(std::move(std::make_unique<ModelResourceFactory>()));

    for (auto &it : Instance().m_foctories) {
      it->Init();
    }
  }

  void ResourceManager::Destroy()
  {
    for (auto &it : Instance().m_foctories) {
      it.release();
    }
    for (auto &it : Instance().m_resources) {
      it.second.reset();
    }
  }

  ResourceManager::SharedResource ResourceManager::GetResource(std::string path)
  {
    if (Instance().IsLoaded(path)) {
      return Instance().m_resources[path];
    }
    //Resource not found
    PKN_DEBUG_ONLY(std::cout << "[Warning] Resource not found"<<std::endl);
    return Instance().LoadResource(path);
  }

  ResourceManager::SharedResource ResourceManager::LoadResource(std::string path , std::string extraPath)
  {
    ResourceManager::SharedResource ret;
    //Already loaded
    if (Instance().IsLoaded(path)) {
      return Instance().m_resources[path];
    }
    //Load
    for (auto &it : Instance().m_foctories) {
      std::size_t pos = path.find(".");
      std::string substr = path.substr(pos);
      if (it->IsCompatible(substr)) {
        auto ptr = it->Load(path, extraPath);
        if (ptr) {
          ret = ResourceManager::SharedResource(ptr);
          Instance().m_resources[path] = ret;
          std::cout << "Resource loaded: " << path << std::endl;
        }
        else {
          ret = it->GetDefaultResource();
          PKN_DEBUG_ONLY(std::cout << "[warning] Resource not found: " << path << std::endl);
        }
        return ret;
      }
    }
    //Codec not found
    PKN_DEBUG_ONLY(std::cout << "[error] Codec not found : " << path << std::endl);
    return ret;
  }

  bool ResourceManager::IsLoaded(std::string path)
  {
    return Instance().m_resources.count(path);
  }

}