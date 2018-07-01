#include "pkn_resource_manager.h"
#include <iostream>
namespace pugaknSDK {
  ResourceManager* ResourceManager::m_instance = nullptr;
  ResourceManager * ResourceManager::Instance()
  {
    if (m_instance == nullptr)
      return m_instance = new ResourceManager();
    else
      return m_instance;
  }

  void ResourceManager::Init()
  {
    Instance()->m_foctories.push_back(std::move(std::make_unique<ShaderResourceFactory>()));
    Instance()->m_foctories.push_back(std::move(std::make_unique<TextureResourceFactory>()));

    for (auto &it : Instance()->m_foctories) {
      it->Init();
    }
  }

  void ResourceManager::Destroy()
  {
    for (auto &it : Instance()->m_foctories) {
      it.release();
    }
    for (auto &it : Instance()->m_resources) {
      it.second.reset();
    }
  }

  ResourceManager::SharedResource ResourceManager::GetResource(std::string path)
  {
    if (Instance()->IsLoaded(path)) {
      return Instance()->m_resources[path];
    }
    //Resource not found
    return Instance()->LoadResource(path);
  }

  ResourceManager::SharedResource ResourceManager::LoadResource(std::string path)
  {
    ResourceManager::SharedResource ret;
    //Already loaded
    if (Instance()->IsLoaded(path)) {
      return Instance()->m_resources[path];
    }
    //Load
    for (auto &it : Instance()->m_foctories) {
      std::size_t pos = path.find(".");
      std::string substr = path.substr(pos);
      if (it->IsCompatible(substr)) {
        auto ptr = it->Load(path);
        if (ptr) {
          ret = ResourceManager::SharedResource(ptr);
          Instance()->m_resources[path] = ret;
          std::cout << "Resource loaded: " << path << std::endl;
        }
        else {
          ret = it->GetDefaultResource();
          std::cout << "[warning] Resource not found: " << path << std::endl;
        }
        return ret;
      }
    }
    //Codec not found
    std::cout << "[error] Codec not found : " << path << std::endl;
    return ret;
  }

  bool ResourceManager::IsLoaded(std::string path)
  {
    return Instance()->m_resources.count(path);
  }

}