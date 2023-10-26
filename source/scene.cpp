#include "scene.h"

Scene::Scene() {
    std::cout << "Created a scene" << std::endl << std::endl;

    cameras.clear();
    lights.clear();
    theRoom.clear();
}

void Scene::addRoom() {

    ColorDBL redColor = ColorDBL(0.6, 0.0, 0.0);
    ColorDBL greenColor = ColorDBL(0.0, 0.6, 0.0);
    ColorDBL blueColor = ColorDBL(0.0, 0.0, 0.6);
    ColorDBL yellowColor = ColorDBL(0.6, 0.6, 0.0);
    ColorDBL magentaColor = ColorDBL(0.6, 0.0, 0.6);
    ColorDBL cyanColor = ColorDBL(0.0, 0.6, 0.6);
    ColorDBL whiteColor = ColorDBL(0.8, 0.8, 0.8);

    int standard = 0;
    int mirror = 1;

    // Wall flying stuff lol
    //theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(7, -1, -1), glm::vec3(7, -1, 1), glm::vec3(7, 1, -1), glm::vec3(7, 1, 1), redColor, standard));
    //Light(glm::vec3(4, -1, 4.9), glm::vec3(4, 1, 4.9), glm::vec3(6, -1, 4.9), glm::vec3(6, 1, 4.9), ColorDBL(1.0, 1.0, 1.0));
    theRoom.push_back(std::make_shared<Triangle>(glm::vec3(4.5, -1, 4.9), glm::vec3(4.5, 1, 4.9), glm::vec3(5.5, -1, 4.9), whiteColor, 2));
    theRoom.push_back(std::make_shared<Triangle>(glm::vec3(5.5, 1, 4.9), glm::vec3(5.5, -1, 4.9), glm::vec3(4.5, 1, 4.9), whiteColor, 2));

    // Ceiling
    theRoom.push_back(std::make_shared<Triangle>(glm::vec3(10, -6, 5),glm::vec3(10, 6, 5),glm::vec3(13, 0, 5),whiteColor, standard));
    theRoom.push_back(std::make_shared<Triangle>(glm::vec3(0, 6, 5), glm::vec3(0, -6, 5), glm::vec3(-3, 0, 5), whiteColor, standard));
    theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(0, 6, 5), glm::vec3(10, 6, 5), glm::vec3(0, -6, 5), glm::vec3(10, -6, 5), whiteColor, standard));

    // Floor
    theRoom.push_back(std::make_shared<Triangle>(glm::vec3(10, 6, -5), glm::vec3(10, -6, -5), glm::vec3(13, 0, -5), whiteColor, standard));
    theRoom.push_back(std::make_shared<Triangle>(glm::vec3(0, 6, -5), glm::vec3(-3, 0, -5),glm::vec3(0, -6, -5), whiteColor, standard));
    theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(0, -6, -5), glm::vec3(10, -6, -5), glm::vec3(0, 6, -5), glm::vec3(10, 6, -5), whiteColor, standard));

    // Wall LF
    theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(10, 6, -5), glm::vec3(13, 0, -5), glm::vec3(10, 6, 5), glm::vec3(13, 0, 5), cyanColor, mirror));

    // Wall L
    theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(0, 6, -5), glm::vec3(10, 6, -5), glm::vec3(0, 6, 5), glm::vec3(10, 6, 5), redColor, standard));

    // Wall LB
    theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(-3, 0, -5), glm::vec3(0, 6, -5), glm::vec3(-3, 0, 5), glm::vec3(0, 6, 5), yellowColor, standard));

    // Wall RF
    theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(13, 0, -5), glm::vec3(10, -6, -5), glm::vec3(13, 0, 5), glm::vec3(10, -6, 5), blueColor, standard));

    // Wall R
    theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(10, -6, -5), glm::vec3(0, -6, -5), glm::vec3(10, -6, 5), glm::vec3(0, -6, 5), greenColor, standard));

    // Wall RB
    theRoom.push_back(std::make_shared<Rectangle>(glm::vec3(0, -6, -5), glm::vec3(-3, 0, -5), glm::vec3(0, -6, 5), glm::vec3(-3, 0, 5), yellowColor, standard));

    std::cout << "Added a room to the scene" << std::endl << std::endl;
}

void Scene::addLight(Light light) {
    std::cout << "Added a light to the scene" << std::endl << std::endl;

    //theRoom.push_back(std::make_shared<Rectangle>(light.surface_));

    lights.push_back(light);
}

void Scene::addCamera(Camera camera) {
    std::cout << "Added a camera to the scene" << std::endl << std::endl;
    cameras.push_back(camera);
}

void Scene::addTetra(Tetrahedron tetra){
    theRoom.push_back((tetra.faces[0]));
    theRoom.push_back((tetra.faces[1]));
    theRoom.push_back((tetra.faces[2]));
    theRoom.push_back((tetra.faces[3]));
}

void Scene::addSphere(Sphere sphere) {
    theRoom.push_back(std::make_shared<Sphere>(sphere));
}

const std::vector<Light>& Scene::getLights() const {
    return lights;
}

const std::vector<Camera>& Scene::getCameras() const {
    return cameras;
}

 const std::vector<std::shared_ptr<Object>>& Scene::getTheRoom() const {
    return theRoom;
}


