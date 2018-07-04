#pragma once
#include "pkn_prerequiites.h"
#include <GL\glew.h>
#include <GLUT\glut.h>
#include "pkn_renderable.h"
#include <MATH/Matrix4D.h>
namespace pugaknSDK {
  class Quad : public IRenderableObject{
  public:
    void Init() override;
    void Draw(const Matrix4D& transform) override;
    void Destroy() override;
  private:
    UInt32 m_index[6];
    Vertex m_vertex[4];
  };
}