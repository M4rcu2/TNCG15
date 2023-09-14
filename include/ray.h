#pragma once

#include "../include/glm/glm.hpp"
#include "../include/colorDBL.h"

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 direction;
    Ray* previousRay;
    Ray* nextRay;
    ColorDBL color;

    // Constructor
    Ray(glm::vec3 start, glm::vec3 direction,ColorDBL color = ColorDBL(0.0, 0.0, 0.0), Ray* prev = nullptr, Ray* next = nullptr);
};
