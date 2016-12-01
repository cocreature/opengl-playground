#pragma once

#include "packed_freelist.h"

#include "GL/gl3w.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <map>
#include <string>
#include <vector>

struct Camera {
    // View
    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 up;

    float aspect;
};

struct Mesh {
    GLuint MeshVAO;
    GLuint PositionBO;
    GLuint VertexCount;
    uint32_t textureID;
};

struct Texture {
    GLuint TexBO;
};

struct Transform {
    glm::vec3 translation;
    glm::quat rotation;
};

struct Instance {
    uint32_t meshID;
    uint32_t transformID;
};

class Scene {
  public:
    Camera camera;
    packed_freelist<Mesh> meshes;
    packed_freelist<Transform> transforms;
    packed_freelist<Instance> instances;
    packed_freelist<Texture> textures;

    void init();
};
