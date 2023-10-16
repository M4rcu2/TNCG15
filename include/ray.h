#pragma once

#include "glm/glm.hpp"
#include "colorDBL.h"
#include "light.h"

class Object; // Forward declaration

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 endVertex;
    glm::vec3 direction;
    Ray* previousRay;
    Ray* nextRay;
    ColorDBL color;
    Object* startingVertexSurface;

    // Constructor
    Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color = ColorDBL(0.0, 0.0, 0.0), Ray* prev = nullptr, Ray* next = nullptr);

    //Cast shadowray and will return the new ColorDBL from the light (if hit)
    ColorDBL castShadowRay(const Object* fromPolygon, const Light& lightsource, const std::vector<Object*>& allPolygons);
};
