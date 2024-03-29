#pragma once
#include "pkn_prerequiites.h"
#include <vector>
#include "pkn_driver.h"
#include "pkn_module.h"

#include "pkn_quad.h"
#include "pkn_cube.h"
#include "pkn_camera.h"
#include "pkn_game_object.h"
#include "pkn_render_target.h"
#include "pkn_light.h"
#include "pkn_mesh.h"
namespace pugaknSDK {
  namespace KEYS {
    enum E {
      UP,
      DOWN,
      RIGHT,
      LEFT,
      COUNT
    };
  }
  //Module Class
  class Application : public Module<Application> {
  public:
    ~Application() = default;
    void Init(Int32 argc, char** argv);
    void Update();
    void Destroy();
    
    void Draw();
    void OnMouseClick(Int32 _button, Int32 _state, Int32 _x, Int32 _y);
    void OnMouseMove(Int32 _x, Int32 _y);
    void OnKeyboardPressed(Int32 _code, Int32 _x, Int32 _y);
    void OnKeyboardReleased(Int32 _code, Int32 _x, Int32 _y);
    void OnKeyboardAsciiPressed(unsigned char _code, Int32 _x, Int32 _y);
    void OnKeyboardAsciiReleased(unsigned char _code, Int32 _x, Int32 _y);
    void OnResize(Int32 _w, Int32 _h);
    

    //GLUT FUNCTIONS
    static void DisplayFunction();
    static void MouseFunction(Int32 _button, Int32 _state, Int32 _x, Int32 _y);
    static void MousePasiveMotionFunction(Int32 _x, Int32 _y);
    static void KeyboardFunction(Int32 _code, Int32 _x, Int32 _y);
    static void KeyboardUpFunction(Int32 _code, Int32 _x, Int32 _y);
    static void KeyboardAsciiFunction(unsigned char _code, Int32 _x, Int32 _y);
    static void KeyboardUpAsciiFunction(unsigned char _code, Int32 _x, Int32 _y);
    static void ReshapeFunc(Int32 _w , Int32 _h);
    static void IdleFunction();
    Quad m_quad;
    Cube m_cube;
  private:
    //Private constructor as this is a Module class
    GameObject m_root;
    GameObject m_skyBox;
    Light m_sunLight;
    Light m_cameraLight;

    RenderTarget m_depthCameraRT;
    RenderTarget m_cubeRT;

    std::vector<Camera> m_cubeCameras;


    std::vector<bool> m_keyStates;
    friend class Module<Application>;
    Application() = default;
  };
}