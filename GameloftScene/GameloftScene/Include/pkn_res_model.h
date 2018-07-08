#pragma once
#include "pkn_prerequiites.h"
#include "pkn_resource_manager.h"
#include "pkn_mesh_parser.h"
#include "pkn_mesh.h"
namespace pugaknSDK {
  class ModelResource : public Resource {
  public:
    Mesh m_mesh;
  };
  class ModelResourceFactory : public ResourceFactory {
  public:
    /**
    * Unused
    */
    void Init() override;

    /**
    * Supported formats: .x
    */
    Resource* Load(std::string path, std::string extraPath = "") override;
    bool IsCompatible(std::string ext) override;
  };

}