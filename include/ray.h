#pragma once

#include "../include/glm/glm.hpp"

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 endVertex; // Optional, may not need it
    glm::vec3 direction;
    //Surface* surface;
    Ray* previousRay;
    Ray* nextRay;
    //ColorRGB color;

    // Constructor for rays with an optional end vertex
    //Ray(glm::vec3 start, glm::vec3 direction, Surface* surface, Ray* prev = nullptr, Ray* next = nullptr, ColorRGB color = ColorRGB(0.0, 0.0, 0.0))
    //    : startVertex(start), direction(direction), surface(surface), previousRay(prev), nextRay(next), color(color) {
    //    // You can set endVertex here if needed based on startVertex and direction
    //}
};

