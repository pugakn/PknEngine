#pragma once
#include "pkn_prerequiites.h"
class Matrix4D;
namespace pugaknSDK {
  struct Vertex {
    float v1, v2, v3, v4;
    float t1, t2;
  };
  class IRenderableObject {
  public:
    virtual void Init() = 0;
    virtual void Draw(const Matrix4D& transform) = 0;
    virtual void Destroy() = 0;

    GLuint m_VB;
    GLuint m_IB;
  };
}