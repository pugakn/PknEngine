#include "pkn_light.h"
namespace pugaknSDK {
  void Light::Init(Vector3D _position, Vector3D _rotation, Vector3D _color, float _radius)
  {
    //m_view = LookAtRH(_position, _target, Vector3D(0, 1, 0));
    //m_positon = _position;
    //m_target = _target;
    _rotation.x *= 3.1416f;
    _rotation.y *= 3.1416f;
    m_camera.Init(_position, _rotation);
    m_color = _color;
    m_radius = _radius;
  }
  //void Light::SetPosition(Vector3D _position)
  //{
  //  m_positon = _position;
  //  m_view = LookAtRH(_position, m_target, Vector3D(0, 1, 0));
  //}
  //void Light::SetTarget(Vector3D _target)
  //{
  //  m_target = _target;
  //}
}

