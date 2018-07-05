#pragma once
#include "pkn_prerequiites.h"
#include <GL\glew.h>
#include <memory>
#include <vector>

class Matrix4D;
namespace pugaknSDK {
  class Texture;
  class Shader;
  struct Vertex {
    float v1, v2, v3;
    float n1, n2, n3;
    float t1, t2;
  };
  class IRenderableObject {
  public:
    virtual void Init() = 0;
    virtual void Draw(const Matrix4D& transform, const std::vector<Texture*>& _textures, Shader* _shader) = 0;
    virtual void Destroy() = 0;

    GLuint m_VB;
    GLuint m_IB;
  };
}