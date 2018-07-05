#include "pkn_application.h"
#include <GLUT/glut.h>
#include <GLUT/freeglut.h>
#include <iostream>
#include "pkn_resource_manager.h"
#include "pkn_time.h"
#include "pkn_res_texture.h"
#include "pkn_res_shader.h"
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

  void Application::KeyboardAsciiFunction(unsigned char _code, Int32 _x, Int32 _y)
  {
    Instance().OnKeyboardAsciiPressed(_code, _x, _y);
  }

  void Application::KeyboardUpAsciiFunction(unsigned char _code, Int32 _x, Int32 _y)
  {
    Instance().OnKeyboardAsciiReleased(_code, _x, _y);
  }

  void Application::ReshapeFunc(Int32 _w, Int32 _h)
  {
    glViewport(0, 0, _w, _h);
    Instance().OnResize(_w,_h);
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
    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    CameraManager::Instance().GetMainCamera().Resize(w, h);

    ResourceManager::LoadResource("vs_quad.glsl", "fs_quad.glsl");
    ResourceManager::LoadResource("vs_pvr.glsl", "fs_pvr.glsl");
    ResourceManager::LoadResource("test.tga");
    m_shadowRT.Create(COLOR_FORMAT::RGBA8, DEPTH_FORMAT::R32, 1, 1024, 1024);
    Driver::Instance().BindBackBufferFBO();

    m_quad.Init();
    m_cube.Init();
    {
      Shader* shBase = &ResourceManager::GetResourceT<ShaderResource>("vs_quad.glsl")->m_shader;
      Shader* shShadow = &ResourceManager::GetResourceT<ShaderResource>("vs_pvr.glsl")->m_shader;

      m_root.AddChild(&m_cube,shShadow);
      m_root.m_children[0]->m_textures.push_back(ResourceManager::GetResourceT<TextureResource>("test.tga")->m_texture.get());
      m_root.AddChild(&m_quad,shBase);
      m_root.m_children[1]->SetRotation(Vector3D(90, 0, 0));
      m_root.m_children[1]->SetScale(Vector3D(100, 100, 100));
      m_root.m_children[1]->SetPosition(Vector3D(0, -5, 0));
      m_root.m_children[1]->UpdateTransform();
    }


    m_keyStates.resize(KEYS::COUNT);

    glutReshapeFunc(&Application::ReshapeFunc);
    glutSpecialFunc(&Application::KeyboardFunction);
    glutSpecialUpFunc(&Application::KeyboardUpFunction);
    glutKeyboardFunc(&Application::KeyboardAsciiFunction);
    glutKeyboardUpFunc(&Application::KeyboardUpAsciiFunction);
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
    for (auto &it : m_root.m_children) {
      it->Draw();
    }
    std::string tString = "FPS: " + std::to_string(Int32(1 / Time::GetDTSeconds()));
    const unsigned char* t = reinterpret_cast<const unsigned char*>(&tString[0]);
    glColor3d(1.0, 0.0, 0.0);
    glRasterPos2f(-0.95, 0.92);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);
    Driver::Instance().SwapBuffers();
  }
  void Application::OnMouseClick(Int32 _button, Int32 _state, Int32 _x, Int32 _y)
  {
  }
  void Application::OnMouseMove(Int32 _x, Int32 _y)
  {
    Camera& mCam = CameraManager::Instance().GetMainCamera();
    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    Vector3D mRot(_x/(float)w,_y/(float)h,0);
    mCam.RotateY(-(mRot.x * 2 - 1));
    mCam.RotateX(-(mRot.y * 2 - 1));
    mCam.Update();
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
  void Application::OnKeyboardAsciiPressed(unsigned char _code, Int32 _x, Int32 _y)
  {
    switch (_code)
    {
    case 'w':
      m_keyStates[KEYS::UP] = true;
      break;
    case 's':
      m_keyStates[KEYS::DOWN] = true;
      break;
    case 'a':
      m_keyStates[KEYS::LEFT] = true;
      break;
    case 'd':
      m_keyStates[KEYS::RIGHT] = true;
      break;
    }
  }
  void Application::OnKeyboardAsciiReleased(unsigned char _code, Int32 _x, Int32 _y)
  {
    switch (_code)
    {
    case 'w':
      m_keyStates[KEYS::UP] = false;
      break;
    case 's':
      m_keyStates[KEYS::DOWN] = false;
      break;
    case 'a':
      m_keyStates[KEYS::LEFT] = false;
      break;
    case 'd':
      m_keyStates[KEYS::RIGHT] = false;
      break;
    }
  }
  void Application::OnResize(Int32 _w, Int32 _h)
  {
    CameraManager::Instance().GetMainCamera().Resize(_w,_h);
  }
  void Application::Destroy()
  {
    Driver::Instance().Destroy();
  }
}