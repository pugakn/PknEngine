#pragma once
#include "pkn_prerequiites.h"
#include <vector>
#include <memory>
namespace pugaknSDK {
  class Texture;
  class RenderTarget {
  public:
    /**
    * Create multiple render targets of length _numRT with _colorFormat and _depthFormat.
    * Leave _w and _h on 0 to set actual window width and height.
    */
    void Create(COLOR_FORMAT::E _colorFormat, DEPTH_FORMAT::E _depthFormat, Int32 _numRT, Int32 _w = 0, Int32 _h = 0);
    
    /**
    * Create a FBO and a cubemap
    */
    void CreateCubemap(COLOR_FORMAT::E _colorFormat, DEPTH_FORMAT::E _depthFormat, Int32 _numRT, Int32 _w = 0, Int32 _h = 0);

    /**
    * Use only if created with Create(...)
    */
    void Bind();

    /**
    * Use only if created with CreateCubemap(...)
    */
    void BindCubeMap(Int32 _i);

    void Destroy();

    Int32 m_width;
    Int32 m_height;
    std::vector<std::shared_ptr<Texture>> m_textures;
    std::vector<std::shared_ptr<Texture>> m_depthTextureCube;
    std::shared_ptr<Texture> m_depthTexture;
  private:
    std::vector<UInt32> m_idList;
  };
}