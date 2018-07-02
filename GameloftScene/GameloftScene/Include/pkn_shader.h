#pragma once
#include "pkn_prerequiites.h"
#include <string>
namespace pugaknSDK {
  class Shader {
  public:
    void CreateFromMemory(std::string _vsSrc, std::string _fsSrc);
    void Bind(Int32 stride);
    UInt32 m_program;
    struct {
      Int32 position;
      Int32 coords;
    } m_attributes;
  };
}