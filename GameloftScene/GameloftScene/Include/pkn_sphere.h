#pragma once
#include "pkn_prerequiites.h"
#include <GL\glew.h>
#include <GLUT\glut.h>
#include "MATH/Matrix4D.h"
#include <vector>
#include <memory>
#include "pkn_renderable.h"
namespace pugaknSDK {
  class Sphere : public IRenderableObject {
  public:
    void Init() override;
    void Draw(const Matrix4D& transform, const std::vector<Texture*>& _textures, Shader* _shader) override;
    void Destroy() override;
  private:
    UInt32 m_index[36];
    Vertex m_vertex[24];
  };
}