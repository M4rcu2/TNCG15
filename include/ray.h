#pragma once

#include "glm/glm.hpp"
#include "colorDBL.h"
#include "light.h"

class Polygon; // Forward declaration
class Sphere;

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 endVertex;
    glm::vec3 direction;
    Ray* previousRay;
    Ray* nextRay;
    ColorDBL color;
    Polygon* startingVertexSurface;
    Sphere* startingSphereSurface;

    // Constructor
    Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color = ColorDBL(0.0, 0.0, 0.0), Ray* prev = nullptr, Ray* next = nullptr);

    //Cast shadowray and will return the new ColorDBL from the light (if hit)
    ColorDBL castShadowRay(const Polygon* fromPolygon, const Light& lightsource, const std::vector<Polygon*>& allPolygons, const std::vector<Sphere*>& allSpheres);

    //Cast shadowray and will return the new ColorDBL from the light (if hit)
    ColorDBL castShadowRay(const Sphere* fromSphere, const Light& lightsource, const std::vector<Sphere*>& allSpheres, const std::vector<Polygon*>& allPolygons);
};
