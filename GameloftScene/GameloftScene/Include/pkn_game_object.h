#pragma once
#include "pkn_prerequiites.h"
#include <memory>
#include <vector>
#include <MATH/Vector3D.h>
#include <MATH/Matrix4D.h>
#include "pkn_renderable.h"

namespace pugaknSDK {
  class Texture;
  class Shader;
  /**
  * A class for a renderable object on the scene
  */
  class GameObject {
  public:
    void Init();
    void Draw();
    void Destroy();

    void SetPosition(const Vector3D& _position);
    void SetRotation(const Vector3D& _rotation);
    void SetScale(const Vector3D& _scale);
    void UpdateTransform();

    void SetRenderComponent(IRenderableObject* _renderComponent);
    IRenderableObject& GetRenderComponent();
    void AddChild(IRenderableObject* _renderComponent);
    std::vector<std::shared_ptr<GameObject>> m_children;


  private:
    Vector3D m_position;
    Vector3D m_rotation;
    Vector3D m_scale;
    Matrix4D m_transform;
    IRenderableObject* m_renderComponent;
  };
}