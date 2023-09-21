#pragma once

#include <vector>
#include "../include/object.h"
#include "../include/light.h"
#include "../include/camera.h" 

class Scene {
public:
    // Constructor
    Scene();

    // Add an object to the scene
    void addObject(Object* object);

    // Add a light to the scene
    void addLight(Light* light);

    // Add a camera
    void addCamera(Camera camera);

    // Get the list of objects in the scene
    const std::vector<Object*>& getObjects() const;

    // Get the list of lights in the scene
    const std::vector<Light*>& getLights() const;

    // Get the list of cameras in the scene
    const std::vector<Camera>& getCameras() const;

private:
    std::vector<Object*> objects; // List of objects in the scene
    std::vector<Light*> lights;   // List of lights in the scene
    std::vector<Camera> cameras; // List of cameras in the scene
};