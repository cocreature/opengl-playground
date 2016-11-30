#include "renderer.h"

#include <GL/gl3w.h>
#include <SDL.h>
#include <iostream>

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &elementBuffer);
}

void Renderer::init(Scene *scene) {
    defaultShader = Shader("../shaders/default.vert", "../shaders/default.frag");

    GLfloat vertices[] = {
        // Positions         // Colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // Top
    };

    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s)
    // and attribute pointer(s).
    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(
        0); // Unbind vertexArray (it's always a good thing to unbind any
            // buffer/array to prevent strange bugs)
}

void Renderer::resize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

void Renderer::paint() {
    if (wireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    defaultShader.use();
    glBindVertexArray(vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

int Renderer::getRenderWidth() const { return windowWidth; }

int Renderer::getRenderHeight() const { return windowHeight; }

void Renderer::toggleWireFrame() { wireFrame = !wireFrame; }
