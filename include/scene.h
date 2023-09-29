#pragma once

#include <vector>
#include "../include/light.h"
#include "../include/camera.h" 
#include "../include/polygon.h" 
#include "../include/colorDBL.h" 

class Scene {
public:
    // Constructor
    Scene();

    // Adds a room in the scene
    void addRoom();

    // Adds a single polygon to the scene
    void addPolygon(Polygon* polygon);        

    // Add a light to the scene
    void addLight(Light* light);

    // Add a camera
    void addCamera(Camera camera);

    // Get the list of lights in the scene
    const std::vector<Light*>& getLights() const;

    // Get the list of cameras in the scene
    const std::vector<Camera>& getCameras() const;
    
    //Get a room baby
    std::vector<Polygon*> getTheRoom() const;

    bool isShadowed(const glm::vec3& point, const Light* light) const;

private:
    std::vector<Light*> lights;   // List of lights in the scene
    std::vector<Camera> cameras; // List of cameras in the scene
    std::vector<Polygon*> theRoom;
};
