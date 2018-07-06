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
      //Textures
      short diffuseText1ID;
      short GlossText2ID;
      short NormalText3ID;
      short SpecularText4ID;
      std::vector<Shader*> m_shaderSet;
      GLint IdCubeLoc;
      unsigned long sig;
      SubsetInfo() {
        sig = 0;
        diffuseText1ID = -1;
        GlossText2ID = -1;
        NormalText3ID = -1;
        SpecularText4ID = -1;
      }
    };
    struct MeshInfo
    {
      std::vector<SubsetInfo> subsetInfo;
      GLuint	 VB;
      std::vector<Vertex> m_vboOriginal;
    };
    std::vector<MeshInfo> m_meshInfo;

    MeshParser parser;
    std::string m_filename;
    void Init() override;
    void Draw(const Matrix4D& transform, const std::vector<Texture*>& _textures, Shader* _shader) override;
    void Destroy() override;
  private:
  };
}