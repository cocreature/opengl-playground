#pragma once

#include <GL/gl3w.h>
#include <memory>
#include <shaderset.h>

class Scene;

class Renderer {
  public:
    ~Renderer();
    void init(Scene *scene);
    void resize(int width, int height);
    void paint();

    int getRenderWidth() const;
    int getRenderHeight() const;
    void toggleWireFrame();

  private:
    bool wireFrame = false;
    int windowWidth;
    int windowHeight;
    GLuint vertexBuffer;
    GLuint elementBuffer;
    GLuint vertexArray;
    ShaderSet shaderSet;
    const GLuint *defaultShader;
    GLuint texture;
};
