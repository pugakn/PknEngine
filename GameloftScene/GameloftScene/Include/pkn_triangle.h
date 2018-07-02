#pragma once
#include "pkn_prerequiites.h"
#include <GL\glew.h>
#include <GLUT\glut.h>
namespace pugaknSDK {
  struct Vertex {
    float v1,v2, v3, v4;
    float t1, t2;
  };
  class Triangle {
  public:
    void Init();
    void Draw();
    void Destroy();
  private:
    UInt16 m_index[6];
    Vertex m_vertex[4];

    GLuint m_VB;
    GLuint m_IB;
  };
}