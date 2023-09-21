#pragma once

#include "../include/glm/glm.hpp"
#include "../include/colorDBL.h"

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 direction;
    // Need to add a pointer to the surface, on which the starting vertex is located
    Ray* previousRay;
    Ray* nextRay;
    ColorDBL color;

    // Constructor
    Ray(glm::vec3 start, glm::vec3 direction,ColorDBL color = ColorDBL(0.0, 0.0, 0.0), Ray* prev = nullptr, Ray* next = nullptr);
};
