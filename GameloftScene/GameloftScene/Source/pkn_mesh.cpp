#include "pkn_mesh.h"
#include <iostream>
#include "pkn_shader.h"
#include "pkn_texture.h"
namespace pugaknSDK {
  void Mesh::Init()
  {
    if (!parser.LoadFile(m_filename.c_str()))
    {
      std::cout << "[Error] Can´t load the .X" << std::endl;
      return;
    }


    for (auto &meshIt : parser.m_meshes)
    {
      m_meshInfo.push_back(MeshInfo());
      m_meshInfo.back().m_vboOriginal = meshIt.m_vbo;
      for (auto &subsetIt : meshIt.m_subsets)
      {
        m_meshInfo.back().subsetInfo.push_back(SubsetInfo());
        //{
        //  //glLinkProgram(m_meshInfo.back().subsetInfo.back().shadersID);
        //  glUseProgram(m_meshInfo.back().subsetInfo.back().shadersID);
        //  //=========================== Create Textures ===============================
        //  int textureID = Tools::LoadTexture(subsetIt.m_effects.m_difusePath.c_str());
        //  m_meshInfo.back().subsetInfo.back().diffuseText1ID = textureID;
        //  if (subsetIt.m_effects.m_glossMap != "")
        //  {
        //    textureID = Tools::LoadTexture(subsetIt.m_effects.m_glossMap.c_str());
        //    m_meshInfo.back().subsetInfo.back().GlossText2ID = textureID;
        //  }
        //  if (subsetIt.m_effects.m_normalMap != "")
        //  {
        //    textureID = Tools::LoadTexture(subsetIt.m_effects.m_normalMap.c_str());
        //    m_meshInfo.back().subsetInfo.back().NormalText3ID = textureID;
        //  }
        //  if (subsetIt.m_effects.m_specularMap != "")
        //  {
        //    textureID = Tools::LoadTexture(subsetIt.m_effects.m_specularMap.c_str());
        //    m_meshInfo.back().subsetInfo.back().SpecularText4ID = textureID;
        //  }

        //  //m_meshInfo.back().subsetInfo.back().IdCubeLoc = glGetUniformLocation(m_meshInfo.back().subsetInfo.back().shadersID, "skybox");
        //}
        //Generar buffer de Indices
        glGenBuffers(1, &m_meshInfo.back().subsetInfo.back().IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshInfo.back().subsetInfo.back().IB);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, subsetIt.m_indexBuffer.size() * sizeof(UInt32), &(subsetIt.m_indexBuffer[0]), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }
      //Generar buffer de vertices
      glGenBuffers(1, &m_meshInfo.back().VB);
      glBindBuffer(GL_ARRAY_BUFFER, m_meshInfo.back().VB);
      glBufferData(GL_ARRAY_BUFFER, meshIt.m_vbo.size() * sizeof(Vertex), &meshIt.m_vbo[0], GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
  }
  void Mesh::Draw(const Matrix4D & transform, const std::vector<Texture*>& _textures, Shader * _shader)
  {
    for (size_t i = 0; i < parser.m_meshes.size(); i++)
    {
      glBindBuffer(GL_ARRAY_BUFFER, m_meshInfo[i].VB);
      for (size_t j = 0; j < parser.m_meshes[i].m_subsets.size(); j++)
      {
        SubsetInfo* sIt = &m_meshInfo[i].subsetInfo[j];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sIt->IB);

        _shader->Bind(sizeof(Vertex), transform);

        size_t indx = 0;
        Int32* ptr = &_shader->m_textures.tex0;
        for (auto &it : _textures)
        {
          it->Bind(*ptr, indx++);
          ptr++;
        }
        //int k = 0;
        //if (sIt->diffuseText1ID != -1)
        //{
        //  glActiveTexture(GL_TEXTURE0 + k);//Set Active texture unit
        //  glBindTexture(GL_TEXTURE_2D, sIt->diffuseText1ID);
        //  glUniform1i(((GLShader*)sIt->m_shaderSet[m_shaderType])->m_locs.textureLoc01, k); //Specify location
        //  k++;
        //}
        //if (sIt->GlossText2ID != -1)
        //{
        //  glActiveTexture(GL_TEXTURE0 + k);
        //  glBindTexture(GL_TEXTURE_2D, sIt->GlossText2ID);
        //  glUniform1i(((GLShader*)sIt->m_shaderSet[m_shaderType])->m_locs.textureLoc02, k);
        //  k++;
        //}
        //if (sIt->NormalText3ID != -1)
        //{
        //  glActiveTexture(GL_TEXTURE0 + k);
        //  glBindTexture(GL_TEXTURE_2D, sIt->NormalText3ID);
        //  glUniform1i(((GLShader*)sIt->m_shaderSet[m_shaderType])->m_locs.textureLoc03, k);
        //  k++;
        //}
        //if (sIt->SpecularText4ID != -1)
        //{
        //  glActiveTexture(GL_TEXTURE0 + k);
        //  glBindTexture(GL_TEXTURE_2D, sIt->SpecularText4ID);
        //  glUniform1i(((GLShader*)sIt->m_shaderSet[m_shaderType])->m_locs.textureLoc04, k);
        //  k++;
        //}
        //glActiveTexture(GL_TEXTURE0 + 5);
        //glBindTexture(GL_TEXTURE_CUBE_MAP, idCube);
        //glUniform1i(sIt->IdCubeLoc, 5);

        glDrawElements(GL_TRIANGLES, parser.m_meshes[i].m_subsets[j].m_indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glUseProgram(0);
      }
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
  }
  void Mesh::Destroy()
  {
  }
}