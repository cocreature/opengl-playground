#pragma once

#include <GL/gl3w.h>
#include <SDL.h>
#include <map>

class Scene;
class Renderer;

class Simulation {
  public:
    Simulation(Scene &scene, Renderer &renderer)
        : pitch(0.0f), yaw(-90.0f), lastFrame(0.0f), scene(scene),
          renderer(renderer) {}
    void handleEvent(const SDL_Event &ev);
    void update();

  private:
    int lastMouseX;
    int lastMouseY;
    // TODO these really belong somewhere else
    GLfloat pitch;
    GLfloat yaw;
    Uint32 lastFrame;
    Scene &scene;
    Renderer &renderer;
    std::map<SDL_Keycode, bool> keys;
};
