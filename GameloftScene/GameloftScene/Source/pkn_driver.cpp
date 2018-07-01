#include "pkn_driver.h"
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <string>
#include <GLUT/glut.h>
namespace pugaknSDK {
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
    std::cout << "GLSL Ver: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
  }
  void Driver::Clear()
  {
    glClearColor(0.2, 0.2, 0.5, 1.0);
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
}