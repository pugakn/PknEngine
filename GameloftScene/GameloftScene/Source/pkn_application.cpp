#include "pkn_application.h"
#include <GLUT/glut.h>
#include <iostream>
namespace pugaknSDK {
  void Application::DisplayFunction()
  {
    Instance().Draw();
  }

  void Application::Init(Int32 argc, char ** argv)
  {
    Driver::StartUp();
    Driver::Instance().Init(argc,argv,&Application::DisplayFunction);
    m_triangle.Init();

    glutDisplayFunc(&Application::DisplayFunction);
    glutMainLoop();
    Update();
  }
  void Application::Update()
  {
    std::cout << "tt";
  }
  void Application::Draw()
  {
    Driver::Instance().Clear();
    m_triangle.Draw();
    Driver::Instance().SwapBuffers();
  }
  void Application::Destroy()
  {
    Driver::Instance().Destroy();
  }
}