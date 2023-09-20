#include "../include/scene.h"
#include "../include/object.h"
#include "../include/light.h"

Scene::Scene() {
    objects.clear();
    lights.clear();
}

void Scene::addObject(Object* object) {
    objects.push_back(object);
}

void Scene::addLight(PointLight* light) {
    lights.push_back(light);
}

const std::vector<Object*>& Scene::getObjects() const {
    return objects;
}

const std::vector<PointLight*>& Scene::getLights() const {
    return lights;
}