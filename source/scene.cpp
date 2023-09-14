#include "../include/scene.h"
#include "../include/object.h"
#include "../include/light.h"

// Constructor
Scene::Scene() {
    // Initialize the scene with empty lists of objects and lights
    objects.clear();
    lights.clear();
}

// Add an object to the scene
void Scene::addObject(Object* object) {
    objects.push_back(object);
}

// Add a light to the scene
void Scene::addLight(Light* light) {
    lights.push_back(light);
}

// Get the list of objects in the scene
const std::vector<Object*>& Scene::getObjects() const {
    return objects;
}


const std::vector<Light*>& Scene::getLights() const {
    return lights;
}