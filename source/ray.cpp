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
        glm::vec3 pointOnLightsource = lightsource.getRandomPointOnLight();

        glm::vec3 lightDirection = glm::normalize(pointOnLightsource - this->endVertex);

        // Create a shadow ray from the hit point to the light source
        Ray castedShadowRay(this->endVertex, lightDirection);

        // Check for intersections with objects in the scene
        if (lightsource.surface_->PointInPolygon(castedShadowRay) != glm::vec3(-100, -100, -100)) {

            float cosThetaX = glm::dot(glm::normalize(fromPolygon->getNormal()), lightDirection);
            float cosThetaY = glm::dot(glm::vec3(0, 0, -1), lightDirection);

            //std::cout << lightsource.getNormal().x << " + " << lightsource.getNormal().y << " + " << lightsource.getNormal().z;

            float denominator = pow(glm::length(lightDirection), 2);

            double lamb = std::max(0.0, ((lightsource.area * 1/3.14f * cosThetaX * cosThetaY) / denominator));

            shadowIntensity += ColorDBL(lamb, lamb, lamb);
        }
        else {
           // The point is in shadow, update shadow intensity accordingly
            shadowIntensity += ColorDBL(0.0, 0.0, 0.0);
        }
    }

    return shadowIntensity;
}
