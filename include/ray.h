#pragma once

#include "glm/glm.hpp"
#include "colorDBL.h"
#include "light.h"
#include "polygon.h"

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 endVertex;
    glm::vec3 direction;
    Ray* previousRay;
    Ray* nextRay;
    ColorDBL color;
    std::shared_ptr<Object> startingVertexSurface;
    

    // Constructor
    Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color = ColorDBL(0.0, 0.0, 0.0), Ray* prev = nullptr, Ray* next = nullptr);

    // Cast shadowray and will return the new ColorDBL from the light (if hit)
    ColorDBL castShadowRay(const std::shared_ptr<Object>& fromObject, const Light& lightsource, const std::vector<std::shared_ptr<Object>>& allObjects);

};
