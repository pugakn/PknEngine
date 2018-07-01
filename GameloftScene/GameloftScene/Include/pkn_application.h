#pragma once
#include "pkn_prerequiites.h"
#include "pkn_driver.h"
#include "pkn_module.h"

#include "pkn_triangle.h"
namespace pugaknSDK {
  //Module Class
  class Application : public Module<Application> {
  public:
    Application() = default;
    ~Application() = default;
    void Init(Int32 argc, char** argv);
    void Update();
    void Destroy();
    
    void Draw();
    
    static void DisplayFunction();

    Triangle m_triangle;
  };
}