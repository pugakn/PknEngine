#pragma once
#include "pkn_prerequiites.h"
#include <MATH/Matrix4D.h>
#include  <MATH/Vector3D.h>
#include "pkn_module.h"
namespace pugaknSDK {
  class Light;
  class Camera {
    const float DEFAULT_FAR_PLANE = 1000.0f;
    const float DEFAULT_NEAR_PLANE = 5.f;
    const float DEFAULT_FOV = 45;
  public:
    void Init(Vector3D _position, Vector3D _rotation);
    void Update();
    void Resize(Int32 _w, Int32 _h);
    void Camera::TraslateFront(float _velocity);
    void Camera::TraslateSide(float _velocity);
    void Camera::RotateX(float _rotation);
    void Camera::RotateY(float _rotation);

    float m_rotX;
    float m_rotY;
    float m_rotationVelocity;
    Vector3D m_position;
    Vector3D m_xDir;
    Vector3D m_yDir;
    Vector3D m_zDir;
    Matrix4D m_projection;
    Matrix4D m_view;
    Matrix4D m_vp;
  };

  //TODO: More complex camera management
  class CameraManager : public Module<CameraManager> {
  public:
    void Init();
    Camera& GetMainCamera();
    Camera& GetActualCamera();
    void SetActualCamera(const Camera& _actual);
    Light* m_shadowLight;
  private:
    Camera m_main;
    Camera* m_actual;
  };

}