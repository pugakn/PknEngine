#include "pkn_triangle.h"

namespace pugaknSDK {
  void Triangle::Init()
  {
    m_vertex[0] = { -1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f };
    m_vertex[1] = { -1.0f, -1.0f, 0.0f, 1.0f,  0.0f, 1.0f };
    m_vertex[2] = { 1.0f, -1.0f, 0.0f, 1.0f,  1.0f, 1.0f };
    m_vertex[3] = { 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f };

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), m_index, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  void Triangle::Draw()
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_VB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);

 /*   glEnableVertexAttribArray(s->vertexAttribLoc);
    glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(s->uvAttribLoc);
    glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(16));*/

    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
  }
  void Triangle::Destroy()
  {
  }
}