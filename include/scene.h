#pragma once

#include <vector>
#include "../include/object.h" // Include your Object class (for storing scene objects)
#include "Light.h"  // Include your Light class (for storing lights)

class Scene {
public:
    // Constructor
    Scene();

    // Add an object to the scene
    void addObject(Object* object);

    // Add a light to the scene
    void addLight(Light* light);

    // Get the list of objects in the scene
    const std::vector<Object*>& getObjects() const;

    // Get the list of lights in the scene
    const std::vector<Light*>& getLights() const;

private:
    std::vector<Object*> objects; // List of objects in the scene
    std::vector<Light*> lights;   // List of lights in the scene
};