#include "pkn_renderable.h"
#include "pkn_shader.h"
namespace pugaknSDK {
  void IRenderableObject::SetShader(const Shader & _shader)
  {
    m_shader = const_cast<Shader*>(&_shader);
  }
}


