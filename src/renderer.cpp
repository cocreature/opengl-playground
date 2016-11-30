#include "renderer.h"

#include <GL/gl3w.h>

void Renderer::init(Scene *scene) {}

void Renderer::resize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

void Renderer::paint() {
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int Renderer::getRenderWidth() const {
    return windowWidth;
}

int Renderer::getRenderHeight() const {
    return windowHeight;
}
