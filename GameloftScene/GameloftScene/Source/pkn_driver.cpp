#include "pkn_driver.h"
#include <iostream>
#include <vector>
#include <string>
#include <GLUT/glut.h>
#include "pkn_utils.h"
namespace pugaknSDK {
  const std::string Driver::SRENSHOOT_FOLDER = "Screenshots/";
  void Driver::Init(Int32 argc, char ** argv, Callback displayFunction)
  {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1080, 720);
    m_hwnd = glutCreateWindow("Pugakn GL");


    GLenum err = glewInit();
    if (GLEW_OK != err) {
      std::cout << "Error: "<< glewGetErrorString(err) << std::endl;
    }
    else {
      std::cout << "GLEW OK" << std::endl;
    }
    std::string GL_Version = std::string((const char*)glGetString(GL_VERSION));
    std::string GL_Extensions = std::string((const char*)glGetString(GL_EXTENSIONS));

    //std::istringstream iss(GL_Extensions);
    //std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
    //  std::istream_iterator<std::string>{} };

    //sExtensionsTok = tokens;
    //Extensions = GL_Extensions;

    //std::cout << "GL Version: " << GL_Version << "\n\nExtensions\n\n";

    //for (unsigned int i = 0; i < ExtensionsTok.size(); i++) {
    //  printf("[%s]\n", ExtensionsTok[i].c_str());
    //}

    const unsigned char *version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "GLSL Version: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    glutWarpPointer(w / 2.0f, h / 2.0f);
    //glutSetCursor(GLUT_CURSOR_NONE);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_FBO);
    for (int i = 0; i < 16; i++) {
      m_drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
  }
  void Driver::Clear(float r, float g, float b, float a)
  {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  void Driver::SwapBuffers()
  {
    glutSwapBuffers();
  }
  void Driver::Destroy()
  {
    glutDestroyWindow(m_hwnd);
  }
  void Driver::BindBackBufferFBO()
  {
    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, w, h);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
  }
  void Driver::Screenshot(std::string _filename)
  {
    static Int32 num = 0;
    std::string modifiedPath = SRENSHOOT_FOLDER + _filename + "_" + std::to_string(num++) + ".bmp";
    std::cout << "Screenshot: " << modifiedPath << std::endl;
    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    byte *buffer = new byte[w * h * 4];
    glReadPixels(0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, buffer);
    Utils::GenerateBitmapImage(buffer, w, h, modifiedPath);

    delete[] buffer;
  }
}