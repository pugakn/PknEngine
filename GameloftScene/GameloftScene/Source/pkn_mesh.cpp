#include "pkn_mesh.h"
#include <iostream>
#include "pkn_shader.h"
#include "pkn_texture.h"
#include "pkn_resource_manager.h"
#include "pkn_res_texture.h"
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
      for (auto &subsetIt : meshIt.m_subsets)
      {
        m_meshInfo.back().subsetInfo.push_back(SubsetInfo());
        {
          //glLinkProgram(m_meshInfo.back().subsetInfo.back().shadersID);
          glUseProgram(m_meshInfo.back().subsetInfo.back().shadersID);
          //=========================== Crete Textures ===============================
          m_meshInfo.back().subsetInfo.back().textures.push_back (
            ((TextureResource*)ResourceManager::LoadResource(subsetIt.m_effects.m_difusePath.c_str()).get())->m_texture.get());
          //if (subsetIt.m_effects.m_glossMap != "")
          //{
          //  textureID = Tools::LoadTexture(subsetIt.m_effects.m_glossMap.c_str());
          //  m_meshInfo.back().subsetInfo.back().GlossText2ID = textureID;
          //}
          //if (subsetIt.m_effects.m_normalMap != "")
          //{
          //  textureID = Tools::LoadTexture(subsetIt.m_effects.m_normalMap.c_str());
          //  m_meshInfo.back().subsetInfo.back().NormalText3ID = textureID;
          //}
          //if (subsetIt.m_effects.m_specularMap != "")
          //{
          //  textureID = Tools::LoadTexture(subsetIt.m_effects.m_specularMap.c_str());
          //  m_meshInfo.back().subsetInfo.back().SpecularText4ID = textureID;
          //}
        }
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
  void Mesh::Draw(const Matrix4D & transform)
  {
    for (size_t i = 0; i < parser.m_meshes.size(); i++)
    {
      glBindBuffer(GL_ARRAY_BUFFER, m_meshInfo[i].VB);
      for (size_t j = 0; j < parser.m_meshes[i].m_subsets.size(); j++)
      {
        SubsetInfo* sIt = &m_meshInfo[i].subsetInfo[j];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sIt->IB);

        m_shader->Bind(sizeof(Vertex), transform);

        size_t indx = 0;
        Int32* ptr = &m_shader->m_textures.tex0;
        for (auto &it : sIt->textures)
        {
          it->Bind(*ptr, indx++);
          ptr++;
        }

        glDrawElements(GL_TRIANGLES, parser.m_meshes[i].m_subsets[j].m_indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        for (size_t i = 0; i < sIt->textures.size(); i++)
        {
          glActiveTexture(GL_TEXTURE0 + i);
          glBindTexture(GL_TEXTURE_2D, 0);
        }
        glUseProgram(0);
      }
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
  }
  void Mesh::Destroy()
  {
  }
}