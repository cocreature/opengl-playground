#include "renderer.h"

#include "scene.h"

#include <GL/gl3w.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &elementBuffer);
}

void Renderer::init(Scene *scene) {
    this->scene = scene;

    shaderSet.SetVersion("330");
    shaderSet.SetPreamble("");

    defaultShader = shaderSet.AddProgramFromExts(
        {"../shaders/default.vert", "../shaders/default.frag"});
}

void Renderer::resize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

void Renderer::paint() {
    shaderSet.UpdatePrograms();
    if (wireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(*defaultShader);
    glEnable(GL_DEPTH_TEST);

    // Camera/View transformation
    glm::mat4 view =
        glm::lookAt(scene->camera.pos, scene->camera.pos + scene->camera.target,
                    scene->camera.up);
    // Projection
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(75.0f),
                                  (GLfloat)windowWidth / (GLfloat)windowHeight,
                                  0.1f, 100.0f);
    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(*defaultShader, "model");
    GLint viewLoc = glGetUniformLocation(*defaultShader, "view");
    GLint projLoc = glGetUniformLocation(*defaultShader, "projection");
    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vertexArray);

    for (uint32_t instanceID : scene->instances) {
        const Instance &instance = scene->instances[instanceID];
        const Mesh &mesh = scene->meshes[instance.meshID];
        const Transform &transform = scene->transforms[instance.transformID];
        const Texture &texture = scene->textures[instance.meshID];

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.TexBO);
        glUniform1i(glGetUniformLocation(*defaultShader, "ourTexture"), 0);

        glm::mat4 modelTransform;
        modelTransform = glm::translate(modelTransform, transform.translation);
        modelTransform = modelTransform * mat4_cast(transform.rotation);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(modelTransform));

        glBindVertexArray(mesh.MeshVAO);
        glDrawArrays(GL_TRIANGLES, 0, mesh.VertexCount);
    }

    glBindVertexArray(0);
}

int Renderer::getRenderWidth() const { return windowWidth; }

int Renderer::getRenderHeight() const { return windowHeight; }

void Renderer::toggleWireFrame() { wireFrame = !wireFrame; }
