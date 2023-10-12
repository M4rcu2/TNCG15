#pragma once
#include "ray.h"
#include "polygon.h"
#include <cmath>


Ray::Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color, Ray* prev, Ray* next)
: startVertex(start), direction(glm::normalize(direction)), previousRay(prev), nextRay(next), color(color)  {   
}

ColorDBL Ray::castShadowRay(const Polygon* fromPolygon, const Light& lightsource,const std::vector<Polygon*>& allPolygons) {
    // Creates a white color
    ColorDBL shadowIntensity = ColorDBL(0.0, 0.0, 0.0);

    // Number of shadow rays
    int nmrOfShadowrays = 5;

    for (int i = 0; i < nmrOfShadowrays; i++) {
        // Get a random point on the light source
        glm::vec3 p = lightsource.getRandomPointOnLight();

        // Create a shadow ray from the hit point to the light source
        Ray castedShadowRay(this->endVertex, glm::normalize(p - this->endVertex));

        // Check for intersections with objects in the scene
        if (lightsource.surface_->PointInPolygon(castedShadowRay) != glm::vec3(-100, -100, -100)) {

            glm::vec3 normal = fromPolygon->getNormal();
            glm::vec3 lightDirection = glm::normalize(p - this->endVertex);

            float cosThetaX = glm::dot(normal, lightDirection);
            float cosThetaY = glm::dot(normal, castedShadowRay.direction);

            float denominator = pow(glm::length(p - this->endVertex), 2);

            double lamb = std::min(1.0, ((lightsource.area * 3.14f * cosThetaX * cosThetaY) / denominator));

            shadowIntensity += ColorDBL(lamb, lamb, lamb);
        }
        else {
           // The point is in shadow, update shadow intensity accordingly
            shadowIntensity += ColorDBL(0.0, 0.0, 0.0);
        }
    }

    return shadowIntensity;
}
