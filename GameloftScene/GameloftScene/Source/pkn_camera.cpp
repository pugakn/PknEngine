#include "pkn_camera.h"
#include <math.h>
namespace pugaknSDK {
  void Camera::Init(Vector3D _position, Vector3D _rotation, bool _usingEulerAngles, float _fov)
  {
    m_usingEulerAngles = _usingEulerAngles;
    m_fov = _fov;
    m_xDir = Vector3D(1,0,0);
    m_yDir = Vector3D(0, 1, 0);
    m_zDir = Vector3D(0, 0, 1);
    m_rotX = _rotation.x;
    m_rotY = _rotation.y;
    m_rotationVelocity = 2.0f;
    m_position = _position;
    m_view = Identity();
    m_projection = PerspectiveFOVRH(ToRadian(_fov), 1280.0f / 720.0f, DEFAULT_NEAR_PLANE, DEFAULT_FAR_PLANE);
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
    m_rotX = _rotation;
  }
  void Camera::RotateY(float _rotation)
  {
    m_rotY = _rotation;
  }

  void Camera::SetPosition(Vector3D _position)
  {
    m_position = _position;
  }
  Matrix4D lookAt(const Vector3D& from, const Vector3D& to, const Vector3D& tmp = Vector3D(0, 1, 0))
  {
    Matrix4D camToWorld;
    Vector3D zaxe = to - from;
    zaxe = Normalize(zaxe);

    Vector3D xaxe;
    xaxe = Cross3(tmp, zaxe);
    xaxe = Normalize(xaxe);

    Vector3D yaxe;
    yaxe = Cross3(zaxe, xaxe);

    camToWorld.m[0][0] = xaxe.x;
    camToWorld.m[0][1] = yaxe.x;
    camToWorld.m[0][2] = zaxe.x;
    camToWorld.m[3][0] = Dot(xaxe, from);
    camToWorld.m[3][0] = -camToWorld.m[3][0];

    camToWorld.m[1][0] = xaxe.y;
    camToWorld.m[1][1] = yaxe.y;
    camToWorld.m[1][2] = zaxe.y;
    camToWorld.m[3][1] = Dot(yaxe, from);
    camToWorld.m[3][1] = -camToWorld.m[3][1];

    camToWorld.m[2][0] = xaxe.z;
    camToWorld.m[2][1] = yaxe.z;
    camToWorld.m[2][2] = zaxe.z;
    camToWorld.m[3][2] = Dot(zaxe, from);
    camToWorld.m[3][2] = -camToWorld.m[3][2];

    camToWorld.m[0][3] = 0.0f;
    camToWorld.m[1][3] = 0.0f;
    camToWorld.m[2][3] = 0.0f;
    camToWorld.m[3][3] = 1.0f;

    return camToWorld;
  }

  Matrix4D lookAtRH(const Vector3D& from, const Vector3D& to, const Vector3D& tmp = Vector3D(0, 1, 0))
  {
    Matrix4D camToWorld;
    Vector3D zaxe = from - to;
    zaxe = Normalize(zaxe);

    Vector3D xaxe;
    xaxe = Cross3(tmp, zaxe);
    xaxe = Normalize(xaxe);

    Vector3D yaxe;
    yaxe = Cross3(zaxe, xaxe);

    camToWorld.m[0][0] = xaxe.x;
    camToWorld.m[0][1] = yaxe.x;
    camToWorld.m[0][2] = zaxe.x;
    camToWorld.m[3][0] = Dot(xaxe, from);
    camToWorld.m[3][0] = -camToWorld.m[3][0];

    camToWorld.m[1][0] = xaxe.y;
    camToWorld.m[1][1] = yaxe.y;
    camToWorld.m[1][2] = zaxe.y;
    camToWorld.m[3][1] = Dot(yaxe, from);
    camToWorld.m[3][1] = -camToWorld.m[3][1];

    camToWorld.m[2][0] = xaxe.z;
    camToWorld.m[2][1] = yaxe.z;
    camToWorld.m[2][2] = zaxe.z;
    camToWorld.m[3][2] = Dot(zaxe, from);
    camToWorld.m[3][2] = -camToWorld.m[3][2];

    camToWorld.m[0][3] = 0.0f;
    camToWorld.m[1][3] = 0.0f;
    camToWorld.m[2][3] = 0.0f;
    camToWorld.m[3][3] = 1.0f;

    return camToWorld;
  }
  void Camera::SetTarget(Vector3D _target)
  {
    m_view = lookAtRH(m_position,_target);
  }

  void Camera::Update()
  {
    if (m_usingEulerAngles) {
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
    else {
      m_vp = m_view*m_projection;
    }

  }
  void Camera::Resize(Int32 _w, Int32 _h)
  {
    m_projection = PerspectiveFOVRH(ToRadian(m_fov), _w / (float)_h, DEFAULT_NEAR_PLANE, DEFAULT_FAR_PLANE);
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