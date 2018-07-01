#include "pkn_application.h"
#include <GLUT/glut.h>

namespace pugaknSDK {
  void Application::DisplayFunction()
  {
    Instance().Draw();
  }

  void Application::Init(Int32 argc, char ** argv)
  {
    Driver::Instance().Init(argc,argv,&Application::DisplayFunction);
  }
  void Application::Update()
  {
  }
  void Application::Draw()
  {
    Driver::Instance().Clear();
    Driver::Instance().SwapBuffers();
  }
  void Application::Destroy()
  {
  }
}