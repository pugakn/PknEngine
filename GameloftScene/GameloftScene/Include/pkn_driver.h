#pragma once
#include "pkn_prerequiites.h"
#include <GL\glew.h>
#include <string>
#include "pkn_module.h"
namespace pugaknSDK {

  /**
  * Module Class do not instantiate!
  * Use this class for graphics api management
  * Usage: Driver::Instance().Init(...);
  */
  class Driver : public Module<Driver>
  {
  public:
    static const std::string SRENSHOOT_FOLDER;
    ~Driver() = default;
    /**
    * Initializate GLUT, GLEW and OpenGL
    */

    void Init(Int32 argc, char** argv, Callback displayFunction);
    /**
    * Clear back buffer color and depth stencil buffer
    */
    void Clear(float r, float g, float b, float a); 

    /**
    * Swap back-front buffers
    */
    void SwapBuffers();

    /**
    * Deallocate memory
    */
    void Destroy();

    void BindBackBufferFBO();

    void Screenshot(std::string _filename);

    //Window handler
    Int32 m_hwnd;

    //Back Bufffer
    GLint	 m_FBO;
    GLenum m_drawBuffers[16];
  private:
    //Private constructor as this is a Module class
    friend class Module<Driver>;
    Driver() = default;
  };
}