#pragma once
#include "pkn_prerequiites.h"
#include <vector>
#include <memory>
namespace pugaknSDK {
  class Texture;
  class RenderTarget {
  public:
    void Create(COLOR_FORMAT::E _colorFormat, DEPTH_FORMAT::E _depthFormat, Int32 _numRT, Int32 _w = 0, Int32 _h = 0);
    void Bind();

    Int32 m_width;
    Int32 m_height;
    std::vector<std::shared_ptr<Texture>> m_textures;
    std::shared_ptr<Texture> m_depthTexture;
  private:
    std::vector<UInt32> m_idList;
  };
}