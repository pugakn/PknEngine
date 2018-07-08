#include "pkn_render_target.h"
#include <GL\glew.h>
#include <GLUT\glut.h>
#include "pkn_texture.h"
#include "pkn_driver.h"
void pugaknSDK::RenderTarget::Create(COLOR_FORMAT::E _colorFormat, DEPTH_FORMAT::E _depthFormat, Int32 _numRT, Int32 _w, Int32 _h)
{
  m_width = _w;
  m_height = _h;
  GLint depth_fmt = GL_DEPTH_COMPONENT; 
  GLint color_fmt;
  GLint cinternal;
  GLint bysize;
  if (_colorFormat == COLOR_FORMAT::RGBA8) {
    color_fmt = GL_RGB;
    cinternal = GL_RGBA;
    bysize = GL_UNSIGNED_BYTE;
  }
  if (_colorFormat == COLOR_FORMAT::RGBA32F) {
    color_fmt = GL_RGB32F;
    cinternal = GL_RGBA;
    bysize = GL_FLOAT;
  }
  GLuint fbo;
  GLuint dtex;

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &dtex);
  glBindTexture(GL_TEXTURE_2D, dtex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, _w, _h, 0, depth_fmt, GL_FLOAT, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, dtex, 0);

  m_depthTexture = std::make_shared<Texture>();
  m_depthTexture->m_id = dtex;
  m_depthTexture->m_width = _w;
  m_depthTexture->m_height = _h;

  m_textures.resize(_numRT);
  for (int i = 0; i < m_textures.size(); i++) {
    GLuint ctex;
    glGenTextures(1, &ctex);
    glBindTexture(GL_TEXTURE_2D, ctex);
    glTexImage2D(GL_TEXTURE_2D, 0, color_fmt, _w, _h, 0, cinternal, bysize, 0);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, ctex, 0);

    m_textures[i] = std::make_shared<Texture>();
    m_textures[i]->m_id = ctex;
    m_textures[i]->m_width = _w;
    m_textures[i]->m_height = _h;
  }
  m_idList.push_back(fbo);
}

void pugaknSDK::RenderTarget::CreateCubemap(COLOR_FORMAT::E _colorFormat, DEPTH_FORMAT::E _depthFormat, Int32 _numRT, Int32 _w, Int32 _h)
{
  m_width = _w;
  m_height = _h;
  GLint depth_fmt = GL_DEPTH_COMPONENT; //GL_DEPTH24_STENCIL8
  GLint color_fmt;
  GLint cinternal;
  GLint bysize;
  if (_colorFormat == COLOR_FORMAT::RGBA8) {
    color_fmt = GL_RGBA;
    cinternal = GL_RGBA;
    bysize = GL_UNSIGNED_BYTE;
  }
  if (_colorFormat == COLOR_FORMAT::RGBA32F) {
    color_fmt = GL_RGBA32F;
    cinternal = GL_RGBA;
    bysize = GL_FLOAT;
  }
  GLuint fbo;
  GLuint dtex;

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &dtex);
  glBindTexture(GL_TEXTURE_CUBE_MAP, dtex);

  for (int i = 0; i < 6; i++) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32F, _w, _h, 0, depth_fmt, GL_FLOAT, 0);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X, dtex, 0);

  m_depthTexture = std::make_shared<Texture>();
  m_depthTexture->m_id = dtex;
  m_depthTexture->m_width = _w;
  m_depthTexture->m_height = _h;

  m_textures.resize(_numRT);
  for (int j = 0; j < m_textures.size(); j++) {
    GLuint ctex;
    glGenTextures(1, &ctex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ctex);

    m_textures[j] = std::make_shared<Texture>();
    m_textures[j]->m_id = ctex;
    m_textures[j]->m_width = _w;
    m_textures[j]->m_height = _h;
    m_textures[j]->m_type = GL_TEXTURE_CUBE_MAP;
    for (int i = 0; i < 6; i++) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, color_fmt, _w, _h, 0, cinternal, bysize, 0);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + j, GL_TEXTURE_CUBE_MAP_POSITIVE_X, ctex, 0);
  }


  m_idList.push_back(fbo);
}

void pugaknSDK::RenderTarget::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_idList[0]);
  glDrawBuffers(m_idList.size(), Driver::Instance().m_drawBuffers);

  glViewport(0, 0, m_width, m_height);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void pugaknSDK::RenderTarget::BindCubeMap(Int32 _i)
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_idList[0]);
  glDrawBuffers(m_idList.size(), Driver::Instance().m_drawBuffers);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + _i, m_depthTexture->m_id, 0);
  for (int i = 0; i < m_textures.size(); i++) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_CUBE_MAP_POSITIVE_X + _i, m_textures[i]->m_id, 0); //GL_DRAW_FRAMEBUFFER
  }
  glViewport(0, 0, m_width, m_height);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
