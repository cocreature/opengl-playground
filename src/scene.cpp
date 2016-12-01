#include "scene.h"

void Scene::init() {
    camera.cameraPos = {0.0f, 0.0f, 3.0f};
    camera.cameraFront = {0.0f, 0.0f, -1.0f};
    camera.cameraUp = {0.0f, 1.0f, 0.0f};
    camera.cameraSpeed = 5.0f;
}
