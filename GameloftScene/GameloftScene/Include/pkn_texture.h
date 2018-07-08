#pragma once
#include "pkn_prerequiites.h"
#include <GL\glew.h>
namespace pugaknSDK {
  class Texture {
  public:
    /**
    * Create a new texture from a memory buffer
    */
    void CreateFromMemory(byte* _buffer, Int32 _w, Int32 _h, Int32 _channels);

    /**
    * Create a new compressed texture from a memory buffer
    * Supported formats: DT1, DXT3, DXT5
    */
    void CreateCompressedFromMemory(byte* _buffer, Int32 _w, Int32 _h, Int32 _channels, UInt64 _fourcc, Int32 _mipCount);


    /**
    * Set texture as part of current rendering state
    * @param _loc uniform location
    * @param _index slot index
    */
    void Bind(Int32 _loc, Int32 _index);

    /**
    * Deallocate memory
    */
    void Destroy();


    Int32 m_width;
    Int32 m_height;
    Int32 m_channels;
    
    Int32 m_type = GL_TEXTURE_2D;
    UInt32 m_id;
  };
}