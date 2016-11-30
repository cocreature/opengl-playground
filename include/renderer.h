#pragma once

#include <memory>

class Scene;

class Renderer {
  public:
    void init(Scene *scene);
    void resize(int width, int height);
    void paint();

    int getRenderWidth() const;
    int getRenderHeight() const;

 private:
    int windowWidth;
    int windowHeight;
};
