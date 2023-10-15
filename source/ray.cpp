#include "ray.h"
#include "polygon.h"
#include <cmath>


Ray::Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color, Ray* prev, Ray* next)
    : startVertex(start), direction(glm::normalize(direction)), previousRay(prev), nextRay(next), color(color) {
}

ColorDBL Ray::castShadowRay(const Polygon* fromPolygon, const Light& lightsource, const std::vector<Polygon*>& allPolygons, const std::vector<Sphere*>& allSpheres) {

    // Creates a white color
    ColorDBL shadowIntensity = ColorDBL(0.0, 0.0, 0.0);

    // Number of shadow rays
    int nmrOfShadowrays = 5;

    const float EPSILON = 10e-2f;

    for (int i = 0; i < nmrOfShadowrays; i++) {

        double v_1 = 1.0;

        // Get a random point on the light source
        glm::vec3 pointOnLight = lightsource.getRandomPointOnLight();
        glm::vec3 pointOnPolygon = this->endVertex;
        glm::vec3 pointOnSphere = this->endVertex;
        glm::vec3 objectPoint = glm::vec3(0,0,0);

        // Calculate distances
        glm::vec3 di = (pointOnLight - pointOnPolygon);
        float di_distance = glm::length(di);
        float di_distance2 = std::numeric_limits<float>::max();

        // Create a shadow ray from the hit point to the light source
        Ray castedShadowRay(pointOnPolygon, glm::normalize(di));

        for(Polygon* p : allPolygons){ // Checks all polygons in the scene

            if( p != fromPolygon && p->collision(castedShadowRay,objectPoint)){ // if point hits something
                    
                float newDistance = glm::length(objectPoint - pointOnPolygon) + EPSILON; // calculates the distance from the polygon to the intersectionpoint

                if (newDistance < di_distance2) { // Want to keep shortest distance to compare

                    di_distance2 = newDistance;
                }
            }
        }         

        for (Sphere* s : allSpheres) { // Checks all spheres in the scene

            if (s->collision(castedShadowRay, objectPoint)) { // if point hits something

                float newDistance = glm::length(objectPoint - pointOnSphere) + EPSILON; // calculates the distance from the polygon to the intersectionpoint

                if (newDistance < di_distance2) { // Want to keep shortest distance to compare

                    di_distance2 = newDistance;
                }
            }
        }
            
        if (di_distance2 < di_distance) { // If di_distance2 is smaller, means that the collision is not on the lightsource, hence something is in the way

            v_1 = 0.0;
        }
                
        // Calculate cosines of the angles between the surface normal and light direction
        float cosThetaX = glm::dot(glm::normalize(fromPolygon->getNormal()), glm::normalize(di));
        float cosThetaY = glm::dot(glm::normalize(lightsource.surface_->getNormal()), glm::normalize(di));

        // Calculate the denominator of the Lambertian reflection formula
        float denominator = pow(abs(di_distance), 2);

        double lamb = std::max(((v_1 * lightsource.area * 3.14f * cosThetaX * (-cosThetaY)) / denominator), 0.0);

        // Update shadow intensity using Lambertian reflection formula
        shadowIntensity += ColorDBL(lamb, lamb, lamb);
            
       
    }

    return shadowIntensity;
}

ColorDBL Ray::castShadowRay(const Sphere* fromSphere, const Light& lightsource, const std::vector<Sphere*>& allSpheres, const std::vector<Polygon*>& allPolygons) {

    // Creates a white color
    ColorDBL shadowIntensity = ColorDBL(0.0, 0.0, 0.0);

    // Number of shadow rays
    int nmrOfShadowrays = 5;

    const float EPSILON = 10e-2f;

    for (int i = 0; i < nmrOfShadowrays; i++) {

        double v_1 = 1.0;

        // Get a random point on the light source
        glm::vec3 pointOnLight = lightsource.getRandomPointOnLight();
        glm::vec3 pointOnPolygon = this->endVertex;
        glm::vec3 pointOnSphere = this->endVertex;
        glm::vec3 objectPoint = glm::vec3(0, 0, 0);

        // Calculate distances
        glm::vec3 di = (pointOnLight - pointOnSphere);
        float di_distance = glm::length(di);
        float di_distance2 = std::numeric_limits<float>::max();

        // Create a shadow ray from the hit point to the light source
        Ray castedShadowRay(pointOnSphere, glm::normalize(di));

        for (Sphere* s : allSpheres) { // Checks all spheres in the scene

            if (s != fromSphere && s->collision(castedShadowRay, objectPoint)) { // if point hits something

                float newDistance = glm::length(objectPoint - pointOnSphere) + EPSILON; // calculates the distance from the polygon to the intersectionpoint

                if (newDistance < di_distance2) { // Want to keep shortest distance to compare

                    di_distance2 = newDistance;
                }
            }
        }

        for (Polygon* p : allPolygons) { // Checks all polygons in the scene

            if (p->collision(castedShadowRay, objectPoint)) { // if point hits something

                float newDistance = glm::length(objectPoint - pointOnPolygon) + EPSILON; // calculates the distance from the polygon to the intersectionpoint

                if (newDistance < di_distance2) { // Want to keep shortest distance to compare

                    di_distance2 = newDistance;
                }
            }
        }

        if (di_distance2 < di_distance) { // If di_distance2 is smaller, means that the collision is not on the lightsource, hence something is in the way

            v_1 = 0.0;
        }

        // Calculate cosines of the angles between the surface normal and light direction
        float cosThetaX = glm::dot(glm::normalize(fromSphere->spheNormal), glm::normalize(di));
        float cosThetaY = glm::dot(glm::normalize(lightsource.surface_->getNormal()), glm::normalize(di));

        // Calculate the denominator of the Lambertian reflection formula
        float denominator = pow(abs(di_distance), 2);

        double lamb = std::max(((v_1 * lightsource.area * 3.14f * cosThetaX * (-cosThetaY)) / denominator), 0.0);

        // Update shadow intensity using Lambertian reflection formula
        shadowIntensity += ColorDBL(lamb, lamb, lamb);


    }

    return shadowIntensity;
}
