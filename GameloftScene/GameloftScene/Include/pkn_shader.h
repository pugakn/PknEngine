#pragma once
#include "pkn_prerequiites.h"
#include <string>
#include <MATH/Matrix4D.h>
namespace pugaknSDK {
  class Shader {
  public:
    /**
    *Create a vertex and fragment shader from a source string
    * @param _vsSrc vertex source code 
    * @param _fsSrc fragment source code
    */
    void CreateFromMemory(std::string _vsSrc, std::string _fsSrc);

    /**
    * Set shader as part of current rendering state
    * @param stride size in bytes of the vertex struct
    * @param world transform matrix
    */
    void Bind(Int32 stride, const Matrix4D& _world);
    UInt32 m_program;
    struct {
      Int32 position;
      Int32 normal;
      Int32 coords;
    } m_attributes;
    struct {
      Int32 tex0;
      Int32 tex1;
      Int32 tex2;
      Int32 tex3;
    } m_textures;
    struct {
      Int32 World;
      Int32 WorldView;
      Int32 WVP;
      Int32 CameraPosition;
      Int32 LightVP;
      Int32 View;
      Int32 LightPositions;
      Int32 LightColors;
      Int32 LightRadius;
      Int32 LightCameraPosition;
    } m_uniforms;
  };
}