#include "pkn_camera.h"
#include <math.h>
namespace pugaknSDK {
  void Camera::Init(Vector3D _position, Vector3D _rotation)
  {
    m_xDir = Vector3D(1,0,0);
    m_yDir = Vector3D(0, 1, 0);
    m_zDir = Vector3D(0, 0, 1);
    m_rotX = _rotation.x;
    m_rotY = _rotation.y;
    m_rotationVelocity = 2.0f;
    m_position = _position;
    m_view = Identity();
    m_projection = PerspectiveFOVRH(ToRadian(DEFAULT_FOV), 1280.0f / 720.0f, DEFAULT_NEAR_PLANE, DEFAULT_FAR_PLANE);
    m_vp = m_view*m_projection;
    Update();
  }

  void Camera::TraslateFront(float _velocity)
  {
    m_position = m_position + _velocity *m_zDir;
  }
  void Camera::TraslateSide(float _velocity)
  {
    m_position = m_position + _velocity *m_xDir;
  }

  void Camera::RotateX(float _rotation)
  {
    m_rotX = _rotation * 3.1416f;
  }
  void Camera::RotateY(float _rotation)
  {
    m_rotY = _rotation * 3.1416f + 1.5708;
  }

  void Camera::Update()
  {
    float cosPitch = cos(m_rotX);
    float sinPitch = sin(m_rotX);
    float cosYaw = cos(m_rotY);
    float sinYaw = sin(m_rotY);

    m_xDir = Vector3D(cosYaw, 0, -sinYaw);
    m_yDir = Vector3D(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
    m_zDir = Vector3D(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

    m_view = Matrix4D(m_xDir.x, m_yDir.x, m_zDir.x, 0,
      m_xDir.y, m_yDir.y, m_zDir.y, 0,
      m_xDir.z, m_yDir.z, m_zDir.z, 0,
      -Dot(m_xDir, m_position), -Dot(m_yDir, m_position), -Dot(m_zDir, m_position), 1.f);
    m_vp = m_view*m_projection;
  }
  void Camera::Resize(Int32 _w, Int32 _h)
  {
    m_projection = PerspectiveFOVRH(ToRadian(DEFAULT_FOV), _w / (float)_h, DEFAULT_NEAR_PLANE, DEFAULT_FAR_PLANE);
    m_vp = m_view*m_projection;
  }
  void CameraManager::Init()
  {
    m_main.Init(Vector3D(0,25,100),Vector3D(0,0,0));
    m_actual = &m_main;
  }
  Camera & CameraManager::GetMainCamera()
  {
    return m_main;
  }
  Camera & CameraManager::GetActualCamera()
  {
    return *m_actual;
  }
  void CameraManager::SetActualCamera(const Camera& _actual)
  {
    m_actual = const_cast<Camera*>(&_actual);
  }
}