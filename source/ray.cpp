#include "ray.h"
#include "polygon.h"
#include <cmath>


Ray::Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color, Ray* prev, Ray* next)
    : startVertex(start), direction(glm::normalize(direction)), previousRay(prev), nextRay(next), color(color) {
}

ColorDBL Ray::castShadowRay(const Polygon* fromPolygon, const Light& lightsource, const std::vector<Polygon*>& allPolygons) {

    // Creates a white color
    ColorDBL shadowIntensity = ColorDBL(0.0, 0.0, 0.0);

    // Number of shadow rays
    int nmrOfShadowrays = 5;

    for (int i = 0; i < nmrOfShadowrays; i++) {

        // Get a random point on the light source
        glm::vec3 p = lightsource.getRandomPointOnLight();

        // Calculate distances
        glm::vec3 di = (p - this->endVertex);
        float di_distance = glm::length(di);

        // Create a shadow ray from the hit point to the light source
        Ray castedShadowRay(this->endVertex, glm::normalize(di));

        // Check for intersections with objects in the scene
        if (lightsource.surface_->PointInPolygon(castedShadowRay) != glm::vec3(-100, -100, -100)) {

            float di_distance2 = std::numeric_limits<float>::max();

            for (Polygon* ptr : allPolygons) {

                if (ptr->PointInPolygon(castedShadowRay) != glm::vec3(-100, -100, -100)) {

                    di_distance2 = glm::length(ptr->PointInPolygon(castedShadowRay) - this->endVertex);
                }
            }            

            float finalDist = glm::min(di_distance, di_distance2);

            //std::cout << finalDist << " + " << di_distance << " + " << di_distance2 << std::endl;

            if (finalDist != di_distance) { // If the distance is not the same, return shadow

                shadowIntensity += ColorDBL(0.0, 0.0, 0.0);
            }
            else { // Otherwise, return calculated color
                
                // Calculate cosines of the angles between the surface normal and light direction
                float cosThetaX = glm::dot(glm::normalize(fromPolygon->normal), glm::normalize(di));
                float cosThetaY = glm::dot(glm::normalize(lightsource.surface_->normal), glm::normalize(di));

                //std::cout << fromPolygon->getNormal().x << " + " << fromPolygon->getNormal().y << " + " << fromPolygon->getNormal().z << std::endl;
                //std::cout << lightsource.surface_->getNormal().x << " + " << lightsource.surface_->getNormal().y << " + " << lightsource.surface_->getNormal().z << std::endl;

                // Calculate the denominator of the Lambertian reflection formula
                float denominator = pow(abs(di_distance), 2);

                double lamb = std::max(((lightsource.area * 3.14f * cosThetaX * (-cosThetaY)) / denominator), 0.0);

                // Update shadow intensity using Lambertian reflection formula
                shadowIntensity += ColorDBL(lamb, lamb, lamb);
            }
        }
    }

    return shadowIntensity;
}