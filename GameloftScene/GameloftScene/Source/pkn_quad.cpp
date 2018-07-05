#include "pkn_quad.h"
#include "pkn_resource_manager.h"
#include "pkn_shader.h"
#include "pkn_res_shader.h"
#include "pkn_texture.h"
#include "pkn_res_texture.h"
namespace pugaknSDK {
  void Quad::Init()
  {
    m_vertex[0] = { -1.0f,  1.0f, 0.0f,   0.0f,0.0f,-1.0f,     0.0f, 0.0f }; //Top-Left
    m_vertex[1] = { -1.0f, -1.0f, 0.0f,   0.0f,0.0f,-1.0f,     0.0f, 1.0f }; //Bootom-Left
    m_vertex[2] = { 1.0f, -1.0f, 0.0f,    0.0f,0.0f,-1.0f,     1.0f, 1.0f };  //Bottom-Right
    m_vertex[3] = { 1.0f,  1.0f, 0.0f,    0.0f,0.0f,-1.0f,     1.0f, 0.0f };  //Top-Right

    m_index[0] = 2;
    m_index[1] = 1;
    m_index[2] = 0;
    m_index[3] = 3;
    m_index[4] = 2;
    m_index[5] = 0;

    glGenBuffers(1, &m_VB);
    glBindBuffer(GL_ARRAY_BUFFER, m_VB);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), &m_vertex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(UInt32), m_index, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  void Quad::Draw(const Matrix4D& transform, const std::vector<Texture*>& _textures, Shader* _shader)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_VB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);

    _shader->Bind(sizeof(Vertex), transform);

    size_t i = 0;
    for (auto &it : _textures)
    {
      it->Bind(_shader->m_textures.tex0, i++);
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

   // for (size_t i = 0; i < _textures.size(); i++)
    {
      //glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    glUseProgram(0);
  }
  void Quad::Destroy()
  {

  }
}