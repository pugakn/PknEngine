#pragma once
#include "pkn_prerequiites.h"
#include "pkn_module.h"
namespace pugaknSDK {
  //Module Class do not instantiate!
  //Use this class for graphics api management
  //Usage: Driver::Instance().Init(...);
  class Driver : public Module<Driver>
  {
  public:
    ~Driver() = default;

    //Initializate GLUT, GLEW and OpenGL
    void Init(Int32 argc, char** argv, Callback displayFunction);
    //Clear back buffer color
    void Clear(); //TODO: Color param
    //Swap back-front buffers
    void SwapBuffers();
    //Deallocate memory
    void Destroy();


    //Window handler
    Int32 m_hwnd;
  private:
    //Private constructor as this is a Module class
    friend class Module<Driver>;
    Driver() = default;
  };
}