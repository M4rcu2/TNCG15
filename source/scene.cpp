#pragma once
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

    // Ceiling
    theRoom.push_back(new Triangle(glm::vec3(10, -6, 5),glm::vec3(10, 6, 5), glm::vec3(13, 0, 5), whiteColor));
    theRoom.push_back(new Triangle(glm::vec3(0, 6, 5), glm::vec3(-3, 0, 5), glm::vec3(0, -6, 5), whiteColor));
    theRoom.push_back(new Rectangle(glm::vec3(0, 6, 5), glm::vec3(10, 6, 5), glm::vec3(0, -6, 5), glm::vec3(10, -6, 5), whiteColor));

    // Floor
    theRoom.push_back(new Triangle(glm::vec3(10, 6, -5), glm::vec3(10, -6, -5), glm::vec3(13, 0, -5), whiteColor));
    theRoom.push_back(new Triangle(glm::vec3(0, 6, -5), glm::vec3(0, -6, -5), glm::vec3(-3, 0, -5), whiteColor));
    theRoom.push_back(new Rectangle(glm::vec3(0, -6, -5), glm::vec3(10, -6, -5),glm::vec3(0, 6, -5), glm::vec3(10, 6, -5), whiteColor));

    // Wall LF
    theRoom.push_back(new Rectangle(glm::vec3(10, 6, -5), glm::vec3(13, 0, -5), glm::vec3(10, 6, 5), glm::vec3(13, 0, 5), blueColor));

    // Wall L
    theRoom.push_back(new Rectangle(glm::vec3(0, 6, -5), glm::vec3(10, 6, -5), glm::vec3(0, 6, 5), glm::vec3(10, 6, 5), redColor));

    // Wall LB
    theRoom.push_back(new Rectangle(glm::vec3(-3, 0, -5), glm::vec3(0, 6, -5), glm::vec3(-3, 0, 5), glm::vec3(0, 6, 5), blueColor));

    // Wall RF
    theRoom.push_back(new Rectangle(glm::vec3(13, 0, -5), glm::vec3(10, -6, -5), glm::vec3(13, 0, 5), glm::vec3(10, -6, 5), cyanColor));

    // Wall R
    theRoom.push_back(new Rectangle(glm::vec3(10, -6, -5), glm::vec3(0, -6, -5), glm::vec3(10, -6, 5), glm::vec3(0, -6, 5), greenColor));

    // Wall RB
    theRoom.push_back(new Rectangle(glm::vec3(0, -6, -5), glm::vec3(-3, 0, -5), glm::vec3(0, -6, 5), glm::vec3(-3, 0, 5), blueColor));

    std::cout << "Added a room to the scene" << std::endl << std::endl;
}

void Scene::addPolygon(Polygon* polygon) {
    theRoom.push_back(polygon);
}

void Scene::addLight(Light light) {
    std::cout << "Added a light to the scene" << std::endl << std::endl;
    lights.push_back(light);
}

void Scene::addCamera(Camera camera) {
    std::cout << "Added a camera to the scene" << std::endl << std::endl;
    cameras.push_back(camera);
}

const std::vector<Light>& Scene::getLights() const {
    return lights;
}

const std::vector<Camera>& Scene::getCameras() const {
    return cameras;
}

std::vector<Polygon*> Scene::getTheRoom() const {
    return theRoom;
}

//bool Scene::isShadowed(const glm::vec3& point, const Light* light) const {
//    // Get the direction from the point to the light source
//    glm::vec3 toLight = glm::normalize(light->getPosition() - point);
//
//    // Create a shadow ray starting from the intersection point and going towards the light source
//    Ray shadowRay(point + 0.01f * toLight, toLight);
//
//    // Check for intersections with objects in the scene
//    for (const Polygon* p : theRoom) {
//        glm::vec3 intersectionPoint = p->PointInPolygon(shadowRay);
//        if (intersectionPoint != glm::vec3(-100, -100, -100)) {
//            // The shadow ray intersects with an object, so the point is in shadow
//            return true;
//        }
//    }
//
//    // No intersections with objects, so the point is not in shadow
//    return false;
//}
