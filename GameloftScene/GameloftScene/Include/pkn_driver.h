#pragma once
#include "pkn_prerequiites.h"
#include "pkn_module.h"
namespace pugaknSDK {
  //Module Class
  class Driver : public Module<Driver>
  {
  public:
    ~Driver() = default;

    void Init(Int32 argc, char** argv, Callback displayFunction);
    void Clear(); //TODO: Color param
    void SwapBuffers();
    void Destroy();
  private:
    Driver() = default;
  };
}