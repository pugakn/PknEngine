#pragma once
#include "pkn_prerequiites.h"
namespace pugaknSDK {
  class Texture {
  public:
    void CreateFromMemory(byte* _buffer, Int32 _w, Int32 _h, Int32 _channels);
    void CreateCompressedFromMemory(byte* _buffer, Int32 _w, Int32 _h, Int32 _channels, UInt64 _fourcc, Int32 _mipCount);

    void Bind(Int32 _loc, Int32 _index);
    void Destroy();
    Int32 m_width;
    Int32 m_height;
    Int32 m_channels;
    
    UInt32 m_id;
  };
}