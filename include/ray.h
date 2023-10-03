#pragma once

#include "../include/glm/glm.hpp"
#include "../include/colorDBL.h"

#include "../include/polygon.h"
class Polygon; // Forward declaration

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 endVertex;
    glm::vec3 direction;
    Ray* previousRay;
    Ray* nextRay;
    ColorDBL color;
    Polygon* startingVertexSurface;

    // Constructor
    Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color = ColorDBL(0.0, 0.0, 0.0), Ray* prev = nullptr, Ray* next = nullptr);

    //Cast shadowray and will return the new ColorDBL from the light (if hit)
    //ColorDBL castShadowRay(const Polygon* pointOnSurface, const Polygon* lightsource, const glm::vec3 pointOnSurface);
};
