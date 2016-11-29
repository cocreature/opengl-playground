#pragma once

#include "GL/gl3w.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <map>
#include <string>
#include <vector>

class Scene {
  public:
    uint32_t MainCameraID;

    void init();
};

void loadMeshes(Scene &scene, const std::string &filename,
                std::vector<uint32_t> *loadedMeshIDs);

void addInstance(Scene &scene, uint32_t meshID, uint32_t *newInstanceID);
