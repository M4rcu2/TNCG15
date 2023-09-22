#include "../include/scene.h"

Scene::Scene() {
    std::cout << "Created a scene" << std::endl << std::endl;

    cameras.clear();
    lights.clear();
}

void Scene::addRoom() {
    
    std::vector<Polygon*> theRoom;

    // Ceiling
    theRoom.push_back(new Triangle(glm::vec3(10, 6, 5), glm::vec3(13, 0, 5), glm::vec3(10, -6, 5)));
    theRoom.push_back(new Triangle(glm::vec3(0, 6, 5), glm::vec3(0, -6, 5), glm::vec3(-3, 0, 5)));
    theRoom.push_back(new Rectangle(glm::vec3(0, 6, 5), glm::vec3(10, 6, 5), glm::vec3(0, -6, 5), glm::vec3(10, -6, 5)));

    // Floor
    theRoom.push_back(new Triangle(glm::vec3(10, 6, -5), glm::vec3(13, 0, -5), glm::vec3(10, -6, -5)));
    theRoom.push_back(new Triangle(glm::vec3(0, 6, -5), glm::vec3(0, -6, -5), glm::vec3(-3, 0, -5)));
    theRoom.push_back(new Rectangle(glm::vec3(0, 6, -5), glm::vec3(10, 6, -5), glm::vec3(0, -6, -5), glm::vec3(10, -6, -5)));

    // Wall LF
    theRoom.push_back(new Rectangle(glm::vec3(10, 6, -5), glm::vec3(13, 0, -5), glm::vec3(10, 6, 5), glm::vec3(13, 0, 5)));

    // Wall L
    theRoom.push_back(new Rectangle(glm::vec3(0, 6, -5), glm::vec3(10, 6, -5), glm::vec3(0, 6, 5), glm::vec3(10, 6, 5)));

    // Wall LB
    theRoom.push_back(new Rectangle(glm::vec3(-3, 0, -5), glm::vec3(0, 6, -5), glm::vec3(-3, 0, 5), glm::vec3(0, 6, 5)));

    // Wall RF
    theRoom.push_back(new Rectangle(glm::vec3(13, 0, -5), glm::vec3(10, -6, -5), glm::vec3(13, 0, 5), glm::vec3(10, -6, 5)));

    // Wall R
    theRoom.push_back(new Rectangle(glm::vec3(10, -6, -5), glm::vec3(0, -6, -5), glm::vec3(10, -6, 5), glm::vec3(0, -6, 5)));

    // Wall RB
    theRoom.push_back(new Rectangle(glm::vec3(0, -6, -5), glm::vec3(-3, 0, -5), glm::vec3(0, -6, 5), glm::vec3(-3, 0, 5)));

    std::cout << "Added a room to the scene" << std::endl << std::endl;
}

void Scene::addLight(Light* light) {
    std::cout << "Added a light to the scene" << std::endl << std::endl;
    lights.push_back(light);
}

void Scene::addCamera(Camera camera) {
    std::cout << "Added a camera to the scene" << std::endl << std::endl;
    cameras.push_back(camera);
}

const std::vector<Light*>& Scene::getLights() const {
    return lights;
}

const std::vector<Camera>& Scene::getCameras() const {
    return cameras;
}