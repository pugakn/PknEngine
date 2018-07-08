#pragma once
#include "pkn_prerequiites.h"
#include <MATH/Vector3D.h>
#include <MATH/Matrix4D.h>
#include "pkn_camera.h"
namespace pugaknSDK {
  class Light {
  public:
    void Init(Vector3D _position, Vector3D _rotation, Vector3D _color, float _radius);
    Camera m_camera;
    Vector3D m_color;
    float m_radius;
  };
}