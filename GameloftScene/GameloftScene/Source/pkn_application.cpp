#include "pkn_application.h"
#include <GLUT/glut.h>
#include <GLUT/freeglut.h>
#include <iostream>
#include "pkn_resource_manager.h"
#include "pkn_time.h"
namespace pugaknSDK {
  void Application::DisplayFunction()
  {
    Instance().Draw();
  }

  void Application::MouseFunction(Int32 _button, Int32 _state, Int32 _x, Int32 _y)
  {
    Instance().OnMouseClick(_button, _state, _x, _y);
  }

  void Application::MousePasiveMotionFunction(Int32 _x, Int32 _y)
  {
    Instance().OnMouseMove(_x,_y);
  }

  void Application::KeyboardFunction(Int32 _code, Int32 _x, Int32 _y)
  {
    Instance().OnKeyboardPressed(_code,_x,_y);
  }

  void Application::KeyboardUpFunction(Int32 _code, Int32 _x, Int32 _y)
  {
    Instance().OnKeyboardReleased(_code, _x, _y);
  }

  void Application::IdleFunction()
  {
    Time::Update();
    Instance().Update();
    glutPostRedisplay();
  }

  void Application::Init(Int32 argc, char ** argv)
  {
    Time::Init();
    Driver::StartUp();
    Driver::Instance().Init(argc,argv,&Application::DisplayFunction);
    ResourceManager::StartUp();
    ResourceManager::Init();
    CameraManager::StartUp();
    CameraManager::Instance().Init();

    ResourceManager::LoadResource("vs_quad.glsl");
    ResourceManager::LoadResource("test.tga");

    m_triangle.Init();
    m_keyStates.resize(KEYS::COUNT);


    glutSpecialFunc(&Application::KeyboardFunction);
    glutSpecialUpFunc(&Application::KeyboardUpFunction);
    glutMouseFunc(&Application::MouseFunction);
    glutPassiveMotionFunc(&Application::MousePasiveMotionFunction);
    glutDisplayFunc(&Application::DisplayFunction);
    glutIdleFunc(&Application::IdleFunction);
    glutMainLoop();
  }
  void Application::Update()
  {
    Camera& mCam = CameraManager::Instance().GetMainCamera();
    const float vel = 10 * Time::GetDTSeconds();
    if (m_keyStates[KEYS::UP]) {
      mCam.TraslateFront(vel * -1);
      mCam.Update();
    }
    if (m_keyStates[KEYS::DOWN]) {
      mCam.TraslateFront(vel);
      mCam.Update();
    }
    if (m_keyStates[KEYS::RIGHT]) {
      mCam.TraslateSide(vel);
      mCam.Update();
    }
    if (m_keyStates[KEYS::LEFT]) {
      mCam.TraslateSide(vel * -1);
      mCam.Update();
    }
  }
  void Application::Draw()
  {
    Driver::Instance().Clear();
    m_triangle.Draw();
    Driver::Instance().SwapBuffers();
  }
  void Application::OnMouseClick(Int32 _button, Int32 _state, Int32 _x, Int32 _y)
  {
  }
  void Application::OnMouseMove(Int32 _x, Int32 _y)
  {
  }
  void Application::OnKeyboardPressed(Int32 _code, Int32 _x, Int32 _y)
  {
      switch (_code)
      {
      case GLUT_KEY_UP:
        m_keyStates[KEYS::UP] = true;
        break;
      case GLUT_KEY_DOWN:
        m_keyStates[KEYS::DOWN] = true;
        break;
      case GLUT_KEY_LEFT:
        m_keyStates[KEYS::LEFT] = true;
        break;
      case GLUT_KEY_RIGHT:
        m_keyStates[KEYS::RIGHT] = true;
        break;
      } 
  }
  void Application::OnKeyboardReleased(Int32 _code, Int32 _x, Int32 _y)
  {
    switch (_code)
    {
    case GLUT_KEY_UP:
      m_keyStates[KEYS::UP] = false;
      break;
    case GLUT_KEY_DOWN:
      m_keyStates[KEYS::DOWN] = false;
      break;
    case GLUT_KEY_LEFT:
      m_keyStates[KEYS::LEFT] = false;
      break;
    case GLUT_KEY_RIGHT:
      m_keyStates[KEYS::RIGHT] = false;
      break;
    }
  }
  void Application::Destroy()
  {
    Driver::Instance().Destroy();
  }
}