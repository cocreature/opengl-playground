#include "simulation.h"

#include "flythrough_camera.h"
#include "scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

template <typename T> static void setToBounds(T &val, T min, T max) {
    val = std::max(std::min(val, max), min);
}

void Simulation::handleEvent(const SDL_Event &ev) {
    if (ev.type == SDL_KEYDOWN) {
        keys[ev.key.keysym.sym] = true;
    } else if (ev.type == SDL_KEYUP) {
        keys[ev.key.keysym.sym] = false;
    }
}

void Simulation::update() {
    Uint32 currentFrame = SDL_GetTicks();
    GLfloat deltaTime = (currentFrame - lastFrame) / 1000.0f;
    SDL_GetRelativeMouseState(&lastMouseX, &lastMouseY);
    lastFrame = currentFrame;
    Camera &camera = scene.camera;

    flythrough_camera_update(value_ptr(camera.pos), value_ptr(camera.target),
                             value_ptr(camera.up), nullptr, deltaTime, 5.0f,
                             0.1f, 80.0f, lastMouseX, lastMouseY, keys[SDLK_UP],
                             keys[SDLK_LEFT], keys[SDLK_DOWN], keys[SDLK_RIGHT],
                             keys[SDLK_SPACE], keys[SDLK_LCTRL], 0);
};
