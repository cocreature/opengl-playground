#pragma once

#include <GL/gl3w.h>

class Shader {
  public:
    Shader() = default;
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
    void use();

  private:
    GLuint program = -1;
};
