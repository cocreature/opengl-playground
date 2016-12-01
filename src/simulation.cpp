#include "simulation.h"

#include "scene.h"

#include <glm/glm.hpp>

void Simulation::handleEvent(const SDL_Event &ev) {
    if (ev.type == SDL_MOUSEMOTION) {
        SDL_GetRelativeMouseState(&lastMouseX, &lastMouseY);
        GLfloat xoffset = lastMouseX;
        GLfloat yoffset = lastMouseY;
        GLfloat sensitivity = 0.05f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        yaw += xoffset;
        pitch += -yoffset;
        pitch = std::max(std::min(pitch, 89.0f), -89.0f);

        glm::vec3 front;
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        scene.camera.cameraFront = glm::normalize(front);
    } else if (ev.type == SDL_KEYDOWN) {
        keys[ev.key.keysym.sym] = true;
    } else if (ev.type == SDL_KEYUP) {
        keys[ev.key.keysym.sym] = false;
    }
}

void Simulation::update() {
    GLfloat currentFrame = SDL_GetTicks() / 1000.0f;
    GLfloat deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    GLfloat cameraSpeed = scene.camera.cameraSpeed * deltaTime;
    if (keys[SDLK_UP]) {
        scene.camera.cameraPos += cameraSpeed * scene.camera.cameraFront;
    }
    if (keys[SDLK_DOWN]) {
        scene.camera.cameraPos -= cameraSpeed * scene.camera.cameraFront;
    }
    if (keys[SDLK_RIGHT]) {
        scene.camera.cameraPos +=
            glm::normalize(
                glm::cross(scene.camera.cameraFront, scene.camera.cameraUp)) *
            cameraSpeed;
    }
    if (keys[SDLK_LEFT]) {
        scene.camera.cameraPos -=
            glm::normalize(
                glm::cross(scene.camera.cameraFront, scene.camera.cameraUp)) *
            cameraSpeed;
    }
};
