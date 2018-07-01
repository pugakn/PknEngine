#pragma once
#include "pkn_prerequiites.h"
#include "pkn_driver.h"
#include "pkn_module.h"
namespace pugaknSDK {
  //Module Class
  class Application : public Module<Application> {
  public:
    ~Application() = default;
    void Init(Int32 argc, char** argv);
    void Update();
    void Destroy();
    
    void Draw();
    
  private:
    Application() = default;
    static void DisplayFunction();
  };
}