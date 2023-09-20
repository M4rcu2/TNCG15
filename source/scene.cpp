#include "../include/scene.h"
#include "../include/object.h"
#include "../include/light.h"
#include "../include/camera.h"
#include <iostream>

Scene::Scene() {
    std::cout << "Created a scene" << std::endl << std::endl;

    cameras.clear();
    objects.clear();
    lights.clear();
}

void Scene::addObject(Object* object) {
    std::cout << "Added an object to the scene" << std::endl << std::endl;
    objects.push_back(object);
}

void Scene::addLight(Light* light) {
    std::cout << "Added a light to the scene" << std::endl << std::endl;
    lights.push_back(light);
}

void Scene::addCamera(Camera camera) {
    std::cout << "Added a camera to the scene" << std::endl << std::endl;
    cameras.push_back(camera);
}

const std::vector<Object*>& Scene::getObjects() const {
    return objects;
}

const std::vector<Light*>& Scene::getLights() const {
    return lights;
}

const std::vector<Camera>& Scene::getCameras() const {
    return cameras;
}