#include "pkn_driver.h"
#include <iostream>
#include <vector>
#include <string>
#include <GLUT/glut.h>
namespace pugaknSDK {

  const int bytesPerPixel = 3; /// red, green, blue
  const int fileHeaderSize = 14;
  const int infoHeaderSize = 40;
  unsigned char* createBitmapFileHeader(int height, int width) {
    int fileSize = fileHeaderSize + infoHeaderSize + bytesPerPixel*height*width;

    static unsigned char fileHeader[] = {
      0,0, /// signature
      0,0,0,0, /// image file size in bytes
      0,0,0,0, /// reserved
      0,0,0,0, /// start of pixel array
    };

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

    return fileHeader;
  }

  unsigned char* createBitmapInfoHeader(int height, int width) {
    static unsigned char infoHeader[] = {
      0,0,0,0, /// header size
      0,0,0,0, /// image width
      0,0,0,0, /// image height
      0,0, /// number of color planes
      0,0, /// bits per pixel
      0,0,0,0, /// compression
      0,0,0,0, /// image size
      0,0,0,0, /// horizontal resolution
      0,0,0,0, /// vertical resolution
      0,0,0,0, /// colors in color table
      0,0,0,0, /// important color count
    };

    infoHeader[0] = (unsigned char)(infoHeaderSize);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(bytesPerPixel * 8);

    return infoHeader;
  }
  void generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName) {

    unsigned char* fileHeader = createBitmapFileHeader(height, width);
    unsigned char* infoHeader = createBitmapInfoHeader(height, width);
    unsigned char padding[3] = { 0, 0, 0 };
    int paddingSize = (4 - (width*bytesPerPixel) % 4) % 4;

    FILE* imageFile;
    fopen_s(&imageFile,imageFileName, "wb");

    fwrite(fileHeader, 1, fileHeaderSize, imageFile);
    fwrite(infoHeader, 1, infoHeaderSize, imageFile);

    int i;
    for (i = 0; i<height; i++) {
      fwrite(image + (i*width*bytesPerPixel), bytesPerPixel, width, imageFile);
      fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
  }

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
  void Driver::Screenshot(std::string path)
  {
    std::cout << "Screenshot: " << path << std::endl;
    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    byte *buffer = new byte[w * h * 4];
    glReadPixels(0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, buffer);
    generateBitmapImage(buffer, h, w, (char*)path.c_str());


    delete[] buffer;
  }
}