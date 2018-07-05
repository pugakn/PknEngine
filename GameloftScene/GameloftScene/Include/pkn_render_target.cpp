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
  if (_colorFormat == COLOR_FORMAT::RGBA8) {
    color_fmt = GL_RGB;
  }
  //if (colorf == COLOR_F::RGBA32) {
  //  color_fmt = GL_RGB32F;
  //}
  GLuint fbo;
  GLuint dtex;

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &dtex);
  glBindTexture(GL_TEXTURE_2D, dtex);
  glTexImage2D(GL_TEXTURE_2D, 0, depth_fmt, _w, _h, 0, depth_fmt, GL_UNSIGNED_INT, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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
    glTexImage2D(GL_TEXTURE_2D, 0, color_fmt, _w, _h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, ctex, 0);

    m_textures[i] = std::make_shared<Texture>();
    m_textures[i]->m_id = ctex;
    m_textures[i]->m_width = _w;
    m_textures[i]->m_height = _h;
    m_idList.push_back(fbo);
  }
}

void pugaknSDK::RenderTarget::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_idList[0]);
  glDrawBuffers(m_idList.size(), Driver::Instance().m_drawBuffers);

  glViewport(0, 0, m_width, m_height);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
