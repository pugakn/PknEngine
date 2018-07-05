#pragma once
#include "pkn_prerequiites.h"
#include <string>
#include <memory>
#include "pkn_resource_manager.h"
#include "pkn_texture.h"

namespace pugaknSDK {
  class TextureResource : public Resource {
  public:
    int m_width;
    int m_height;
    int m_pitch;
    int m_channels;
    int m_size;
    std::vector<unsigned char> m_pixels;
    std::unique_ptr<Texture> m_texture;
  };
  class TextureResourceFactory : public ResourceFactory {
  public:
    void Init() override;
    Resource* Load(std::string path, std::string extraPath = "") override;
    bool IsCompatible(std::string ext) override;
  };
}