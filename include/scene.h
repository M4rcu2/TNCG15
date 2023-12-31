#pragma once

#include <vector>
#include "polygon.h" 
#include "light.h"
#include "camera.h" 
#include "colorDBL.h" 

class Scene {
public:
    // Constructor
    Scene();

    // Adds a room in the scene
    void addRoom();       

    // Add a light to the scene
    void addLight(Light light);

    // Add a camera
    void addCamera(Camera camera);

    // Get the list of lights in the scene
    const std::vector<Light>& getLights() const;

    // Get the list of cameras in the scene
    const std::vector<Camera>& getCameras() const;
    
    // Get a room baby
    const std::vector<std::shared_ptr<Object>>& getTheRoom() const;
    
    //Add tetrahedra
    void addTetra(Tetrahedron tetra); 

    //Add Sphere
    void addSphere(Sphere sphere);

private:
    std::vector<Light> lights;   // List of lights in the scene
    std::vector<Camera> cameras; // List of cameras in the scene
    std::vector<std::shared_ptr<Object>> theRoom;

};
