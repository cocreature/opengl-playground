#pragma once

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

class Scene {
  public:
    Camera camera;

    void init();
};

void loadMeshes(Scene &scene, const std::string &filename,
                std::vector<uint32_t> *loadedMeshIDs);

void addInstance(Scene &scene, uint32_t meshID, uint32_t *newInstanceID);
