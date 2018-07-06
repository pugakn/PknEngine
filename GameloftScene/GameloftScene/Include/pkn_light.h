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
    //void SetPosition(Vector3D _position);
    //void SetTarget(Vector3D _target);
    //Matrix4D m_view;
    Vector3D m_color;
    //Vector3D m_positon;
    //Vector3D m_target;
    float m_radius;
  };
}