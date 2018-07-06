#include "pkn_res_texture.h"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
namespace pugaknSDK {
  void TextureResourceFactory::Init()
  {
    //m_defaultResource = std::make_shared<TextureResource>();
    //auto ptr = ((TextureResource*)m_defaultResource.get());
    //ptr->m_channels = g_chkr.bytes_per_pixel;
    //ptr->m_height = g_chkr.height;
    //ptr->m_width = g_chkr.width;
    //ptr->m_pitch = ptr->m_width * ptr->m_channels;
    //ptr->m_size = ptr->m_height * ptr->m_pitch;
    //ptr->m_pixels.assign((unsigned char*)g_chkr.pixel_data, (unsigned char*)g_chkr.pixel_data + ptr->m_size);
  }
  Resource * TextureResourceFactory::Load(std::string path, std::string extraPath)
  {
    TextureResource* res = new TextureResource();
    res->m_texture = std::make_unique<Texture>();
    bool found = false;
    std::string basePath = "";
    std::string path_ = basePath;
    std::string filepath = path_ + std::string(path);
    std::ifstream inf(filepath.c_str());
    found = inf.good();
    inf.close();
    if (!found) {
      PKN_DEBUG_ONLY(std::cout << "[Warning] Resource not loaded: " << path << std::endl);
      return nullptr;
    }

    int x = 0, y = 0, channels = 0;
    unsigned char *buffer = 0;

    std::size_t pos = path.find(".");
    std::string substr = path.substr(pos);
    if (substr == ".dds") {
      unsigned char header[124];

      FILE *fp;

      fopen_s(&fp,path.c_str(), "rb");
      if (fp == NULL)
      {
        PKN_DEBUG_ONLY(std::cout << "[Warning] Resource not loaded: " << path << std::endl);
        return nullptr;
      }

      char filecode[4];
      fread(filecode, 1, 4, fp);
      if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        PKN_DEBUG_ONLY(std::cout << "[Warning] Resource not loaded: " << path << std::endl);
        return nullptr;
      }

      fread(&header, 124, 1, fp);
      y = *(unsigned int*)&(header[8]);
      x = *(unsigned int*)&(header[12]);
      unsigned int linearSize = *(unsigned int*)&(header[16]);
      unsigned int mipMapCount = *(unsigned int*)&(header[24]);
      unsigned int fourCC = *(unsigned int*)&(header[80]);


      unsigned int bufsize;
      
      bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
      buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
      fread(buffer, 1, bufsize, fp);
      fclose(fp);

      channels = (fourCC == FOURCC_DXT1) ? 3 : 4;




      res->m_size = x * y * channels;
      res->m_width = x;
      res->m_height = y;
      res->m_channels = channels;
      res->m_pitch = res->m_width * res->m_channels;
      //res->m_pixels.assign(buffer, buffer + res->m_size);
      res->m_texture->CreateCompressedFromMemory(buffer, res->m_width, res->m_height, res->m_channels, fourCC, mipMapCount);

    }
    else {
      buffer = stbi_load(filepath.c_str(), &x, &y, &channels, 0);
      if (!buffer) {
        PKN_DEBUG_ONLY(std::cout << "[Warning] Resource not loaded: " << path << std::endl);
        return nullptr;
      }
      res->m_size = x * y * channels;
      res->m_width = x;
      res->m_height = y;
      res->m_channels = channels;
      res->m_pitch = res->m_width * res->m_channels;
      res->m_pixels.assign(buffer, buffer + res->m_size);
      stbi_image_free(buffer);
      res->m_texture->CreateFromMemory(res->m_pixels.data(), res->m_width, res->m_height, res->m_channels);
    }





    return res;
  }
  bool TextureResourceFactory::IsCompatible(std::string ext)
  {
    return ext == ".tga" || ext == ".dds";
  }
}