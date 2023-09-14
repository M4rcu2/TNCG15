#pragma once

#include "../include/glm/glm.hpp"
#include "../include/colorDBL.h"

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 endVertex;
    glm::vec3 direction;
    Ray* previousRay;
    Ray* nextRay;
    ColorDBL color;

    // Constructor
    Ray(glm::vec3 start, glm::vec3 direction, Ray* prev = nullptr, Ray* next = nullptr, ColorDBL color = ColorDBL(0.0, 0.0, 0.0))
        : startVertex(start), direction(direction), previousRay(prev), nextRay(next), color(color) {
        
    }
};

