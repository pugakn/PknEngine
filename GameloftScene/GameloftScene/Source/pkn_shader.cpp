#include "pkn_shader.h"
#include <GL\glew.h>
#include <iostream>
#include "pkn_camera.h"
#include "pkn_light.h"
namespace pugaknSDK {
  void checkcompilederrors(GLuint shader, GLenum type) {
    GLint bShaderCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &bShaderCompiled);
    if (!bShaderCompiled) {
      int i32InfoLogLength, i32CharsWritten;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

      char* pszInfoLog = new char[i32InfoLogLength];
      glGetShaderInfoLog(shader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
      if (type == GL_FRAGMENT_SHADER) {
        std::cout << "Fragment shader compilation failed\n";
      }
      else if (type == GL_VERTEX_SHADER) {
        std::cout << "Vertex shader compilation failed\n";
      }
      std::cout << pszInfoLog  << std::endl;
      delete[] pszInfoLog;
    }
  }
  GLuint createShader(GLenum type, byte* pSource) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char**)&pSource, NULL);
    glCompileShader(shader);
    PKN_DEBUG_ONLY(checkcompilederrors(shader, type));
    return shader;
  }
  void Shader::CreateFromMemory(std::string _vsSrc, std::string _fsSrc)
  {
    m_program = glCreateProgram();
    GLuint vshader_id = createShader(GL_VERTEX_SHADER, (byte*)_vsSrc.c_str());
    GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, (byte*)_fsSrc.c_str());

    glAttachShader(m_program, vshader_id);
    glAttachShader(m_program, fshader_id);

    glLinkProgram(m_program);
    glUseProgram(m_program);

    m_attributes.position = glGetAttribLocation(m_program, "Position");
    m_attributes.normal = glGetAttribLocation(m_program, "Normal");
    m_attributes.coords = glGetAttribLocation(m_program, "Coords");

    m_textures.tex0 = glGetUniformLocation(m_program, "tex0");
    m_textures.tex1 = glGetUniformLocation(m_program, "tex1");
    m_textures.tex2 = glGetUniformLocation(m_program, "tex2");
    m_textures.tex3 = glGetUniformLocation(m_program, "tex3");

    m_uniforms.World = glGetUniformLocation(m_program, "World");
    m_uniforms.WorldView = glGetUniformLocation(m_program, "WorldView");
    m_uniforms.WVP = glGetUniformLocation(m_program, "WVP");
    m_uniforms.CameraPosition = glGetUniformLocation(m_program, "CameraPosition");
    m_uniforms.LightVP = glGetUniformLocation(m_program, "LightVP");
    m_uniforms.LightPositions = glGetUniformLocation(m_program, "LightPositions");
    m_uniforms.LightColors = glGetUniformLocation(m_program, "LightColors");
    m_uniforms.LightRadius = glGetUniformLocation(m_program, "LightRadius");
  }

  void Shader::Bind(Int32 stride, const Matrix4D& _world)
  {
    glUseProgram(m_program);
    Camera& mCam = CameraManager::Instance().GetActualCamera();
    Matrix4D wordView = _world * mCam.m_view;
    Matrix4D WVP = _world * mCam.m_vp;
    if (m_uniforms.World > -1)
      glUniformMatrix4fv(m_uniforms.World, 1, GL_FALSE, &_world.m[0][0]);
    if (m_uniforms.WorldView > -1)
      glUniformMatrix4fv(m_uniforms.WorldView, 1, GL_FALSE, &wordView.m[0][0]);
    if (m_uniforms.WVP > -1)
      glUniformMatrix4fv(m_uniforms.WVP, 1, GL_FALSE, &WVP.m[0][0]);
    if (m_uniforms.LightVP > -1)
      glUniformMatrix4fv(m_uniforms.LightVP, 1, GL_FALSE, &CameraManager::Instance().m_lights[0]->m_camera.m_vp.m[0][0]);
    if (m_uniforms.CameraPosition > -1)
      glUniform4fv(m_uniforms.CameraPosition, 1, &mCam.m_position.x);
    Vector4D lp[2]{Vector4D( CameraManager::Instance().m_lights[0]->m_camera.m_position,1),Vector4D(CameraManager::Instance().m_lights[1]->m_camera.m_position,1) };
    Vector4D lc[2]{ Vector4D(CameraManager::Instance().m_lights[0]->m_color,1) ,Vector4D(CameraManager::Instance().m_lights[1]->m_color,1) };
    Vector4D lr[2]{ Vector4D(CameraManager::Instance().m_lights[0]->m_radius,1,1,1) ,Vector4D(CameraManager::Instance().m_lights[1]->m_radius,1,1,1) };
    if (m_uniforms.LightPositions > -1)
      glUniform4fv(m_uniforms.LightPositions, 2, &lp[0].x);
    if (m_uniforms.LightColors > -1)
      glUniform4fv(m_uniforms.LightColors, 2, &lc[0].x);
    if (m_uniforms.LightRadius > -1)
      glUniform4fv(m_uniforms.LightRadius, 2, &lr[0].x);


    glEnableVertexAttribArray(m_attributes.position);
    glVertexAttribPointer(m_attributes.position, 3, GL_FLOAT, GL_FALSE, stride, PKN_BUFFER_OFFSET(0));
    glEnableVertexAttribArray(m_attributes.normal);
    glVertexAttribPointer(m_attributes.normal, 3, GL_FLOAT, GL_FALSE, stride, PKN_BUFFER_OFFSET(12));
    glEnableVertexAttribArray(m_attributes.coords);
    glVertexAttribPointer(m_attributes.coords, 2, GL_FLOAT, GL_FALSE, stride, PKN_BUFFER_OFFSET(24));
  }

}
