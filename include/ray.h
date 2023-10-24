#pragma once

#include "glm/glm.hpp"
#include "colorDBL.h"
#include "light.h"
#include "polygon.h"
#include <glm/gtx/string_cast.hpp>  //print glm::vec
class Scene; // Forward declaration

class Ray {
public:
    glm::vec3 startVertex;
    glm::vec3 endVertex;
    glm::vec3 direction;
    Ray* previousRay;
    Ray* nextRay;
    ColorDBL color;
    std::shared_ptr<Object> startingVertexSurface;  //TF IS THIS?
    

    // Constructor
    Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color = ColorDBL(0.0, 0.0, 0.0), Ray* prev = nullptr, Ray* next = nullptr);

    // Cast shadowray and will return the new ColorDBL from the light (if hit)
    ColorDBL castShadowRay(const std::shared_ptr<Object>& fromObject, const Light& lightsource, const std::vector<std::shared_ptr<Object>>& allObjects);
    ColorDBL reflectionRecursion(const int nmrOfReflections, const Scene& theScene);
    glm::vec3 newBounceDirection(const glm::vec3& normal);  //returns a new direction in the hemisphere where the normal is in the middle
    glm::vec3 randomGaussValue(glm::vec3 normal);
    
    //print ray
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray) {
        os << "Ray class: ------------------------------------------------------\n";
        os << "Start Vertex: " << glm::to_string(ray.startVertex) << std::endl;
        os << "End Vertex: " << glm::to_string(ray.endVertex) << std::endl;
        os << "Direction: " << glm::to_string(ray.direction) << std::endl;
        os << "Color: " << ray.color << std::endl;
        os << "-----------------------------------------------------------------\n";

        // You can add more properties to print as needed

        return os;
    }

};
