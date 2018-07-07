#pragma once
#include "pkn_prerequiites.h"
#include <GL\glew.h>
#include <GLUT\glut.h>
#include "MATH/Matrix4D.h"
#include <vector>
#include <memory>
#include <string>
#include "pkn_renderable.h"
#include "pkn_mesh_parser.h"
namespace pugaknSDK {
  class Mesh : public IRenderableObject {
  public:
    struct SubsetInfo
    {
      GLuint shadersID;
      GLuint	IB;
      std::vector<Texture*> textures;
      unsigned long sig;
      SubsetInfo() {
        sig = 0;
      }
    };
    struct MeshInfo
    {
      std::vector<SubsetInfo> subsetInfo;
      GLuint VB;
    };
    std::vector<MeshInfo> m_meshInfo;

    MeshParser parser;
    std::string m_filename;
    void Init() override;
    void Draw(const Matrix4D& transform) override;
    void Destroy() override;
  private:
  };
}