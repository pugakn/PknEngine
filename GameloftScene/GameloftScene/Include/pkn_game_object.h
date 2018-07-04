#pragma once
#include "pkn_prerequiites.h"
#include <memory>
#include <vector>
namespace pugaknSDK {
  class GameObject {
    void Init();
    void Draw();
    void Destroy();
  private:
    std::vector<std::shared_ptr<GameObject>> m_children; //TODO: Root-> update all
  };
}