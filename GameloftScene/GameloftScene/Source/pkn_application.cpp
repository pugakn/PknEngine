#include "pkn_application.h"
#include <GLUT/glut.h>
#include <GLUT/freeglut.h>
#include <iostream>
#include "pkn_resource_manager.h"
#include "pkn_time.h"
#include "pkn_res_texture.h"
#include "pkn_res_shader.h"
#include "pkn_res_model.h"
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
    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    ResourceManager::StartUp();
    ResourceManager::Init();
    CameraManager::StartUp();
    CameraManager::Instance().Init();
    ResourceManager::LoadResource("vs_quad.glsl", "fs_quad.glsl");
    ResourceManager::LoadResource("vs_inv_cube.glsl", "fs_light.glsl");
    ResourceManager::LoadResource("vs_light.glsl", "fs_light.glsl");
    ResourceManager::LoadResource("vs_reflect.glsl", "fs_reflect.glsl");
    ResourceManager::LoadResource("vs_cube.glsl", "fs_cube.glsl");
    ResourceManager::LoadResource("wall.tga");
    ResourceManager::LoadResource("diffuse_TGA_DXT5_1.dds");
    ResourceManager::LoadResource("ahriFire.x");
    ResourceManager::LoadResource("Vi.x");
    ResourceManager::LoadResource("Darius.x");
    ResourceManager::LoadResource("Jinx.x");

    ResourceManager::LoadResource("ahri.x");
    ResourceManager::LoadResource("sona.x");
    ResourceManager::LoadResource("grag.x");
    ResourceManager::LoadResource("garen.x");
    ResourceManager::LoadResource("Vi.x");
   // ResourceManager::LoadResource("anie.x");

    
    m_depthCameraRT.Create(COLOR_FORMAT::RGBA8, DEPTH_FORMAT::R32, 1, w, h);
    m_cubeRT.CreateCubemap(COLOR_FORMAT::RGBA8, DEPTH_FORMAT::R32,1, 1024, 1024);
    m_sunLight.Init(Vector3D(0, 100, 200),Vector3D(-0.1,2, 0),Vector3D(0.8,0.8,0.8),50000);

    m_cameraLight.Init(Vector3D(0, 3, 120), Vector3D(ToRadian(45), ToRadian(0), 0), Vector3D(0.7, 0.5, 0.5), 200);
    CameraManager::Instance().m_lights.push_back(&m_sunLight);
    CameraManager::Instance().m_lights.push_back(&m_cameraLight);

    m_sunLight.m_camera.m_usingEulerAngles = false;
    m_sunLight.m_camera.SetTarget(Vector3D(0,20,0),Vector3D(0,1,0));

    CameraManager::Instance().SetActualCamera(CameraManager::Instance().GetMainCamera());
    CameraManager::Instance().GetMainCamera().Resize(w, h);
    CameraManager::Instance().SetActualCamera(m_sunLight.m_camera);
    CameraManager::Instance().GetActualCamera().Resize(w, h);
    CameraManager::Instance().SetActualCamera(CameraManager::Instance().GetMainCamera());
    Driver::Instance().BindBackBufferFBO();

    m_cubeCameras.resize(6);
    m_cubeCameras[0].Init(Vector3D(0, 30, 200), Vector3D(0, ToRadian(90), 0),false,90);
    m_cubeCameras[1].Init(Vector3D(0, 30, 200), Vector3D(0, ToRadian(-90), 0), false,90);
    m_cubeCameras[2].Init(Vector3D(0, 30, 200), Vector3D(0, ToRadian(0), ToRadian(90)), false, 90);
    m_cubeCameras[3].Init(Vector3D(0, 30, 200), Vector3D(0, ToRadian(0), ToRadian(-90)), false, 90);
    m_cubeCameras[4].Init(Vector3D(0, 30, 200), Vector3D(ToRadian(0), ToRadian(180), 0), false,90);
    m_cubeCameras[5].Init(Vector3D(0, 30, 200), Vector3D(ToRadian(0), ToRadian(0), 0), false,90);

    for (size_t i = 0; i < 6; i++)
    {
      m_cubeCameras[i].Resize(1024,1024);
    }

    m_cubeCameras[0].SetTarget(m_cubeCameras[0].m_position + Vector3D(10, 0, 0) , Vector3D(0,-1,0));
    m_cubeCameras[1].SetTarget(m_cubeCameras[1].m_position + Vector3D(-10, 0, 0), Vector3D(0, -1, 0));
    m_cubeCameras[2].SetTarget(m_cubeCameras[2].m_position + Vector3D(0, 10, 0), Vector3D(0, 0, -1));
    m_cubeCameras[3].SetTarget(m_cubeCameras[3].m_position + Vector3D(0, -10, 0),Vector3D(0, 0, -1));
    m_cubeCameras[4].SetTarget(m_cubeCameras[4].m_position + Vector3D(0, 0, 10),Vector3D(0, -1, 0));
    m_cubeCameras[5].SetTarget(m_cubeCameras[5].m_position + Vector3D(0, 0, -10),Vector3D(0, -1, 0));
    for (size_t i = 0; i < 6; i++)
    {
      m_cubeCameras[i].Update();
    }
    m_quad.Init();
    m_cube.Init();

    Mesh& mesh = ResourceManager::GetResourceT<ModelResource>("ahriFire.x")->m_mesh;
    Mesh& ahri = ResourceManager::GetResourceT<ModelResource>("garen.x")->m_mesh;
    Mesh& darius = ResourceManager::GetResourceT<ModelResource>("Darius.x")->m_mesh;
    Mesh& jinx = ResourceManager::GetResourceT<ModelResource>("Jinx.x")->m_mesh;

    Mesh&  ahri2 = ResourceManager::GetResourceT<ModelResource>("ahri.x")->m_mesh;
    Mesh&  sona = ResourceManager::GetResourceT<ModelResource>("sona.x")->m_mesh;
    Mesh&  grag = ResourceManager::GetResourceT<ModelResource>("grag.x")->m_mesh;
    Mesh&  garen = ResourceManager::GetResourceT<ModelResource>("anie.x")->m_mesh;
    Mesh& vi = ResourceManager::GetResourceT<ModelResource>("Vi.x")->m_mesh;

    mesh.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    mesh.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());
    ahri.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    ahri.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());
    darius.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    darius.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());
    jinx.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    jinx.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());

    ahri2.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    ahri2.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());

    sona.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    sona.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());

    grag.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    grag.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());

    garen.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    garen.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());

    vi.m_meshInfo.back().subsetInfo.back().textures.resize(2);
    vi.m_meshInfo.back().subsetInfo.back().textures[1] = (m_depthCameraRT.m_depthTexture.get());


    {
      Shader* shBase = &ResourceManager::GetResourceT<ShaderResource>("vs_quad.glsl")->m_shader;
      Shader* shShadow = &ResourceManager::GetResourceT<ShaderResource>("vs_light.glsl")->m_shader;
      Shader* shReflect = &ResourceManager::GetResourceT<ShaderResource>("vs_reflect.glsl")->m_shader;

      mesh.m_shader = shShadow;
      m_quad.m_shader = shShadow;
      m_cube.m_shader = shShadow;
      m_quad.m_textures.push_back(ResourceManager::GetResourceT<TextureResource>("diffuse_TGA_DXT5_1.dds")->m_texture.get());
      m_quad.m_textures.push_back(ResourceManager::GetResourceT<TextureResource>("wall.tga")->m_texture.get());
      m_quad.m_textures.push_back(ResourceManager::GetResourceT<TextureResource>("wall.tga")->m_texture.get());

      m_cube.m_textures.push_back(ResourceManager::GetResourceT<TextureResource>("wall.tga")->m_texture.get());
      m_cube.m_textures.push_back(ResourceManager::GetResourceT<TextureResource>("wall.tga")->m_texture.get());
      m_cube.m_textures.push_back(ResourceManager::GetResourceT<TextureResource>("wall.tga")->m_texture.get());

      m_root.AddChild(&m_cube);
      m_root.m_children[0]->SetScale(Vector3D(30, 30, 30));
      m_root.m_children[0]->SetPosition(Vector3D(0, 30, 200));
      m_root.m_children[0]->UpdateTransform();
      m_root.AddChild(&m_quad);
      m_root.m_children[1]->SetRotation(Vector3D(90, 0, 0));
      m_root.m_children[1]->SetScale(Vector3D(250, 250, 250));
      m_root.m_children[1]->SetPosition(Vector3D(0, 0, 0));
      m_root.m_children[1]->UpdateTransform();

      m_root.AddChild(&darius);
      m_root.m_children[2]->SetScale(Vector3D(5, 5, 5));
      m_root.m_children[2]->SetPosition(Vector3D(40, 0, 0));
      m_root.m_children[2]->UpdateTransform();

      m_root.AddChild(&jinx);
      m_root.m_children[3]->SetScale(Vector3D(1, 1, 1));
      m_root.m_children[3]->SetPosition(Vector3D(80, 0, 40));
      m_root.m_children[3]->UpdateTransform();

      m_root.AddChild(&mesh);
      m_root.m_children[4]->SetScale(Vector3D(1, 1, 1));
      m_root.m_children[4]->SetPosition(Vector3D(-40, 0, 0));
      m_root.m_children[4]->UpdateTransform();

      m_root.AddChild(&ahri);
      m_root.m_children[5]->SetScale(Vector3D(1, 1, 1));
      m_root.m_children[5]->SetPosition(Vector3D(-80, 0, 0));
      m_root.m_children[5]->UpdateTransform();

      m_root.AddChild(&ahri2);
      m_root.m_children[6]->SetScale(Vector3D(1, 1, 1));
      m_root.m_children[6]->SetPosition(Vector3D(0, 70, 0));
      m_root.m_children[6]->UpdateTransform();

      m_root.AddChild(&grag);
      m_root.m_children[7]->SetScale(Vector3D(1, 1, 1));
      m_root.m_children[7]->SetPosition(Vector3D(40, 70, 50));
      m_root.m_children[7]->UpdateTransform();

      m_root.AddChild(&garen);
      m_root.m_children[8]->SetScale(Vector3D(1, 1, 1));
      m_root.m_children[8]->SetPosition(Vector3D(-40, 70, 50));
      m_root.m_children[8]->UpdateTransform();

      m_root.AddChild(&sona);
      m_root.m_children[9]->SetScale(Vector3D(1, 1, 1));
      m_root.m_children[9]->SetPosition(Vector3D(-120, 0, 50));
      m_root.m_children[9]->UpdateTransform();

      m_root.AddChild(&vi);
      m_root.m_children[10]->SetScale(Vector3D(1, 1, 1));
      m_root.m_children[10]->SetPosition(Vector3D(120, 0, 50));
      m_root.m_children[10]->UpdateTransform();


      m_skyBox.SetRenderComponent(&m_cube);
      m_skyBox.SetScale(Vector3D(250, 250, 250));
      m_skyBox.SetPosition(Vector3D(-0, 0, 0));
      m_skyBox.UpdateTransform();
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
    Camera& mCam = CameraManager::Instance().GetActualCamera();
    const float vel = 50 * Time::GetDTSeconds();
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
    m_cameraLight.m_camera.SetPosition(mCam.m_position);
    m_cameraLight.m_camera.Update();
  }
  void Application::Draw()
  {
    CameraManager::Instance().SetActualCamera(m_sunLight.m_camera);
    m_depthCameraRT.Bind();
    //Driver::Instance().Clear(0,0,0,1);
    for (auto &it : m_root.m_children) {
      it->GetRenderComponent().m_shader = (&ResourceManager::GetResourceT<ShaderResource>("vs_quad.glsl")->m_shader);
      it->Draw();
    }
    for (size_t i = 0; i < 6; i++)
    {
      CameraManager::Instance().SetActualCamera(m_cubeCameras[i]);
      m_cubeRT.BindCubeMap(i);
      Int32 index = 0;
      for (auto &it : m_root.m_children) {
        if (index == 0) {
        }
        else {
          it->GetRenderComponent().m_shader = (&ResourceManager::GetResourceT<ShaderResource>("vs_cube.glsl")->m_shader);
          it->Draw();
        }
        index++;
      }
      m_cube.SetShader(ResourceManager::GetResourceT<ShaderResource>("vs_inv_cube.glsl")->m_shader);
      glCullFace(GL_BACK);
      m_skyBox.Draw();
      glCullFace(GL_FRONT);
    }

    


    Driver::Instance().BindBackBufferFBO();
    CameraManager::Instance().SetActualCamera(CameraManager::Instance().GetMainCamera());
    //
    //CameraManager::Instance().SetActualCamera(m_sunLight.m_camera);
    Driver::Instance().Clear(0.2,0.2,0.5,1);

    //m_cube.SetShader((ResourceManager::GetResourceT<ShaderResource>("vs_light.glsl")->m_shader));
    m_cube.SetShader(ResourceManager::GetResourceT<ShaderResource>("vs_inv_cube.glsl")->m_shader);
    glCullFace(GL_BACK);
    m_skyBox.Draw();
    glCullFace(GL_FRONT);
    Int32 i = 0;

    m_cube.m_textures[1] = (m_depthCameraRT.m_depthTexture.get());
    m_cube.m_textures[2] = (m_cubeRT.m_textures[0].get());

    m_quad.m_textures[1] = (m_depthCameraRT.m_depthTexture.get());
    m_quad.m_textures[2] = (m_cubeRT.m_textures[0].get());

    for (auto &it : m_root.m_children) {
      if (i == 0) {
        Shader* shReflect = &ResourceManager::GetResourceT<ShaderResource>("vs_reflect.glsl")->m_shader;
        it->GetRenderComponent().m_shader =  (shReflect);
      }
      else {
        it->GetRenderComponent().m_shader = (&ResourceManager::GetResourceT<ShaderResource>("vs_light.glsl")->m_shader);
      }
      it->Draw();
      i++;
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
    const float vel = 3;
    mCam.RotateY(-(mRot.x * 2 - 1)*vel);
    mCam.RotateX(-(mRot.y * 2 - 1)*vel);
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
    case 'e':
      Driver::Instance().Screenshot("screenshot");
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
    CameraManager::Instance().SetActualCamera(CameraManager::Instance().GetMainCamera());
    CameraManager::Instance().GetMainCamera().Resize(_w, _h);
    CameraManager::Instance().SetActualCamera(m_sunLight.m_camera);
    CameraManager::Instance().GetActualCamera().Resize(_w, _h);
    CameraManager::Instance().SetActualCamera(CameraManager::Instance().GetMainCamera());
  }
  void Application::Destroy()
  {
    Driver::Instance().Destroy();
  }
}