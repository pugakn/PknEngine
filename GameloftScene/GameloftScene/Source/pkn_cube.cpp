#include "pkn_cube.h"
#include "pkn_resource_manager.h"
#include "pkn_res_shader.h"
#include "pkn_res_texture.h"
namespace pugaknSDK {
  void Cube::Init()
  {
    // +Y SIDE
    m_vertex[0] = { -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,    1.0f, 1.0f };
    m_vertex[1] = { 1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f };
    m_vertex[2] = { -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f,    1.0f, 0.0f };
    m_vertex[3] = { 1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f };

    // -Y SIDE
    m_vertex[4] = { -1.0f,  -1.0f, -1.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f };
    m_vertex[5] = { 1.0f,  -1.0f, -1.0f,    0.0f, -1.0f, 0.0f,   1.0f, 0.0f };
    m_vertex[6] = { -1.0f,  -1.0f,  1.0f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f };
    m_vertex[7] = { 1.0f,  -1.0f,  1.0f,    0.0f, -1.0f, 0.0f,   1.0f, 1.0f };

    // +X SIDE
    m_vertex[8] = { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f };
    m_vertex[9] = { 1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f };
    m_vertex[10] = { 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f };
    m_vertex[11] = { 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f };

    // -X SIDE
    m_vertex[12] = { -1.0f,  1.0f,  1.0f,   -1.0f, 0.0f, 0.0f,   1.0f, 0.0f };
    m_vertex[13] = { -1.0f,  1.0f, -1.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f };
    m_vertex[14] = { -1.0f, -1.0f,  1.0f,   -1.0f, 0.0f, 0.0f,   1.0f, 1.0f };
    m_vertex[15] = { -1.0f, -1.0f, -1.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 1.0f };

    // +Z SIDE
    m_vertex[16] = { -1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f };
    m_vertex[17] = { 1.0f,  1.0f, 1.0f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f };
    m_vertex[18] = { -1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f };
    m_vertex[19] = { 1.0f, -1.0f, 1.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f };

    // -Z SIDE
    m_vertex[20] = { -1.0f,  1.0f, -1.0f,   0.0f, 0.0f, -1.0f,  1.0f, 0.0f };
    m_vertex[21] = { 1.0f,  1.0f, -1.0f,    0.0f, 0.0f, -1.0f,  0.0f, 0.0f };
    m_vertex[22] = { -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f };
    m_vertex[23] = { 1.0f, -1.0f, -1.0f,    0.0f, 0.0f, -1.0f,  0.0f, 1.0f };

    // +X
    m_index[0] = 8;
    m_index[1] = 9;
    m_index[2] = 10;
    m_index[3] = 9;
    m_index[4] = 11;
    m_index[5] = 10;

    // -X
    m_index[6] = 14;
    m_index[7] = 13;
    m_index[8] = 12;
    m_index[9] = 14;
    m_index[10] = 15;
    m_index[11] = 13;

    // +Y
    m_index[12] = 1;
    m_index[13] = 2;
    m_index[14] = 0;
    m_index[15] = 3;
    m_index[16] = 2;
    m_index[17] = 1;

    // -Y
    m_index[18] = 4;
    m_index[19] = 6;
    m_index[20] = 5;
    m_index[21] = 5;
    m_index[22] = 6;
    m_index[23] = 7;

    // +Z
    m_index[24] = 17;
    m_index[25] = 18;
    m_index[26] = 16;
    m_index[27] = 19;
    m_index[28] = 18;
    m_index[29] = 17;

    // -Z
    m_index[30] = 20;
    m_index[31] = 22;
    m_index[32] = 21;
    m_index[33] = 21;
    m_index[34] = 22;
    m_index[35] = 23;


    glGenBuffers(1, &m_VB);
    glBindBuffer(GL_ARRAY_BUFFER, m_VB);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(Vertex), &m_vertex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(UInt32), m_index, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  void Cube::Draw(const Matrix4D & transform, const std::vector<Texture*>& _textures, Shader* _shader)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_VB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
    _shader->Bind(sizeof(Vertex), transform);
    size_t i = 0;
    Int32* ptr = &_shader->m_textures.tex0;
    for (auto &it : _textures)
    {
      it->Bind(*ptr, i++);
      ptr++;
    }

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    for (size_t i = 0; i < _textures.size(); i++)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    glUseProgram(0);
  }
  void Cube::Destroy()
  {
  }
}