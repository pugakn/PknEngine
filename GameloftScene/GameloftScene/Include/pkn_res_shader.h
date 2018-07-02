#pragma once
#include "pkn_prerequiites.h"
#include "pkn_resource_manager.h"
#include "pkn_shader.h"
namespace pugaknSDK {
  class ShaderResource : public Resource {
  public:
    std::string m_source;
    Shader m_shader;
  };
  class ShaderResourceFactory : public ResourceFactory {
  public:
    void Init() override;
    Resource* Load(std::string path) override;
    bool IsCompatible(std::string ext) override;
  };

}