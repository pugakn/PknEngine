#include "pkn_game_object.h"
#include "pkn_res_texture.h"
#include "pkn_shader.h"
namespace pugaknSDK {
  void GameObject::Init()
  {
  }

  void GameObject::Draw()
  {
    PKN_ASSERT(m_renderComponent);//
    m_renderComponent->Draw(m_transform);
  }

  void GameObject::Destroy()
  {
  }

  void GameObject::SetPosition(const Vector3D & _position)
  {
    m_position = _position;
  }

  void GameObject::SetRotation(const Vector3D & _rotation)
  {
    m_rotation = _rotation;
  }

  void GameObject::SetScale(const Vector3D & _scale)
  {
    m_scale = _scale;
  }

  void GameObject::UpdateTransform()
  {
    Matrix4D scale = Scaling(m_scale.x, m_scale.y, m_scale.z);
    Matrix4D rotationX = RotationX(ToRadian(m_rotation.x));
    Matrix4D rotationY = RotationY(ToRadian(m_rotation.y));
    Matrix4D rotationZ = RotationZ(ToRadian(m_rotation.z));
    Matrix4D position = Translation(m_position.x, m_position.y, m_position.z);
    m_transform = scale*rotationX*rotationY*rotationZ*position;
  }

  void GameObject::SetRenderComponent(IRenderableObject * _renderComponent)
  {
    m_renderComponent = _renderComponent;
  }
  IRenderableObject & GameObject::GetRenderComponent()
  {
    return *m_renderComponent;
  }
  void GameObject::AddChild(IRenderableObject * _renderComponent)
  {
    m_children.push_back(std::make_shared<GameObject>());
    m_children.back()->SetRenderComponent(_renderComponent);
  }
}

