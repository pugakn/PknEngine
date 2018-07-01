#include "pkn_driver.h"
#include <GLUT/glut.h>
namespace pugaknSDK {
  void Driver::Init(Int32 argc, char ** argv, Callback displayFunction)
  {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1080, 720);
    glutCreateWindow("Pugakn GL");

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glutDisplayFunc(displayFunction);
    glutMainLoop();
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
  }
}