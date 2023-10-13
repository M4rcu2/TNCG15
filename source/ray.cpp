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
        if (lightsource.surface_->PointInPolygon(castedShadowRay) != glm::vec3(-100, -100, -100)) {     //should always be true;
            int hits = 0;
            for(Polygon* p : allPolygons){
                if(p != fromPolygon){
                    if(p->PointInPolygon(castedShadowRay) != glm::vec3(-100, -100, -100)){
                        hits++;
                    }
                }
            }
            if(hits<=2){
                glm::vec3 normal = fromPolygon->getNormal();
                glm::vec3 lightDirection = glm::normalize(p - this->endVertex);
                
                // Calculate cosines of the angles between the surface normal and light direction
                float cosThetaX = glm::dot(glm::normalize(fromPolygon->getNormal()), glm::normalize(di));
                float cosThetaY = glm::dot(glm::normalize(lightsource.surface_->getNormal()), glm::normalize(di));

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
