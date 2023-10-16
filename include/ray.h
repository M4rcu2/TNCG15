#pragma once

#include "glm/glm.hpp"
#include "colorDBL.h"
#include "light.h"
//#include "scene.h"    //Försökte fixa så ray tar in scene

class Polygon; // Forward declaration
class Scene;

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
    ColorDBL castShadowRay(const Polygon* fromPolygon, const Light& lightsource, const std::vector<Polygon*>& allPolygons);
    ColorDBL reflectionRecursion(const int nmrOfReflections, const Scene& theScene);
    glm::vec3 newBounceDirection(const glm::vec3& normal);  //returns a new direction in the hemisphere where the normal is in the middle
    float randomGaussValue(glm::vec3 normal);

};
