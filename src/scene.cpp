#include "scene.h"

void Scene::init() {
    camera.pos = {0.0f, 0.0f, 3.0f};
    camera.target = {0.0f, 0.0f, -1.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
}
