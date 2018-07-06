#include "pkn_texture.h"
#include "pkn_res_texture.h"
namespace pugaknSDK {
  void Texture::CreateFromMemory(byte* _buffer, Int32 _w, Int32 _h, Int32 _channels)
  {
    m_width = _w;
    m_height = _h;
    m_channels = _channels;

    unsigned int glFormat = 0;
    unsigned int glChannel = GL_UNSIGNED_BYTE;
    unsigned int glTarget = GL_TEXTURE_2D;

    //if (this->props&TEXT_BASIC_FORMAT::CH_ALPHA)
    //  glFormat = GL_ALPHA;
    //else if (this->props&TEXT_BASIC_FORMAT::CH_RGB)
    //  glFormat = GL_RGB;
    //else if (this->props&TEXT_BASIC_FORMAT::CH_RGBA)
    glFormat = GL_RGBA;

    glGenTextures(1, &m_id);
    glBindTexture(glTarget, m_id);

    if (this->m_width % 4 != 0)
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    else
      glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glTexImage2D(glTarget, 0, glFormat, m_width, m_height, 0, glFormat, glChannel, (void*)(_buffer));

    glGenerateMipmap(glTarget);

    
    //Params

    unsigned int glFiltering = 0;
    unsigned int glWrap = 0;

    glFiltering = GL_LINEAR_MIPMAP_LINEAR;
    glWrap = GL_REPEAT;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFiltering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFiltering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);

    int Max = 17;
    glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Max);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Max);

    glBindTexture(GL_TEXTURE_2D, 0);
  }
  void Texture::CreateCompressedFromMemory(byte * _buffer, Int32 _w, Int32 _h, Int32 _channels, UInt64 _fourcc, Int32 _mipCount)
  {
    m_width = _w;
    m_height = _h;
    m_channels = _channels;
    unsigned int glTarget = GL_TEXTURE_2D;

    glGenTextures(1, &m_id);
    glBindTexture(glTarget, m_id);

    UInt32 format;
    switch (_fourcc)
    {
    case TextureResourceFactory::FOURCC_DXT1:
      format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
    case TextureResourceFactory::FOURCC_DXT3:
      format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      break;
    case TextureResourceFactory::FOURCC_DXT5:
      format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
    }

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    //Load Mip Maps
    for (unsigned int level = 0; level < _mipCount && (_w || _h); ++level)
    {
      unsigned int size = ((_w + 3) / 4)*((_h + 3) / 4)*blockSize;
      glCompressedTexImage2D(GL_TEXTURE_2D, level, format, _w, _h,
        0, size, _buffer + offset);
      offset += size;
      _w /= 2;
      _h /= 2;
    }
    //glGenerateMipmap(glTarget);

    //Params
    unsigned int glFiltering = 0;
    unsigned int glWrap = 0;

    glFiltering = GL_LINEAR_MIPMAP_LINEAR;
    glWrap = GL_REPEAT;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFiltering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFiltering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);

    int Max = 17;
    glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Max);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Max);

    glBindTexture(GL_TEXTURE_2D, 0);
  }
  void Texture::Bind(Int32 _loc, Int32 _index)
  {
    if (_loc < 0) return;
    glActiveTexture(GL_TEXTURE0 + _index);
    glBindTexture(m_type, m_id);
    glUniform1i(_loc, _index);
  }
  void Texture::Destroy()
  {
    glDeleteTextures(1, &m_id);
  }
}

