#include "pkn_texture.h"
#include <GL\glew.h>
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
    glBindTexture(GL_TEXTURE_2D, m_id);

    unsigned int glFiltering = 0;
    unsigned int glWrap = 0;

    glFiltering = GL_LINEAR_MIPMAP_LINEAR;
    glWrap = GL_REPEAT;

    //if (params & TEXT_BASIC_PARAMS::MIPMAPS)
    //  glFiltering = GL_LINEAR_MIPMAP_LINEAR;

    //if (params & TEXT_BASIC_PARAMS::CLAMP_TO_EDGE)
    //  glWrap = GL_CLAMP_TO_EDGE;

    //if (params & TEXT_BASIC_PARAMS::TILED)
    //  glWrap = GL_REPEAT;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFiltering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFiltering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);

    int Max = 1;
    glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Max);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Max);

    glBindTexture(GL_TEXTURE_2D, 0);
  }
  void Texture::CreateCompressedFromMemory(byte * _buffer, Int32 _w, Int32 _h, Int32 _channels)
  {
  }
  void Texture::Bind(Int32 _loc, Int32 _index)
  {
    if (_loc < 0) return;
    glActiveTexture(GL_TEXTURE0 + _index);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glUniform1i(_loc, _index);
  }
  void Texture::Destroy()
  {
    glDeleteTextures(1, &m_id);
  }
}

