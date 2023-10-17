#include "ray.h"
#include "polygon.h"
#include "scene.h"  //Tar in scene för att använda
#include <random>
#include <cmath>


Ray::Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color, Ray* prev, Ray* next)
    : startVertex(start), direction(glm::normalize(direction)), previousRay(prev), nextRay(next), color(color) {
}

ColorDBL Ray::castShadowRay(const std::shared_ptr<Object>& fromObject, const Light& lightsource, const std::vector<std::shared_ptr<Object>>& allObjects) {

    // Creates a black color
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
        glm::vec3 di = (pointOnLight - pointOnPolygon);
        float di_distance = glm::length(di);
        float di_distance2 = std::numeric_limits<float>::max();

        // Create a shadow ray from the hit point to the light source
        Ray castedShadowRay(pointOnPolygon, glm::normalize(di));

        for (std::shared_ptr<Object> o : allObjects) { // Checks all polygons in the scene

            if (o != fromObject && o->collision(castedShadowRay, objectPoint)) { // if point hits something

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
        float cosThetaX = glm::dot(glm::normalize(fromObject->getNormal()), glm::normalize(di));
        float cosThetaY = glm::dot(glm::normalize(lightsource.surface_.getNormal()), glm::normalize(di));

        // Calculate the denominator of the Lambertian reflection formula
        float denominator = static_cast<float>(pow(abs(di_distance), 2));

        double lamb = std::max(((v_1 * lightsource.area * 3.14f * cosThetaX * (-cosThetaY)) / denominator), 0.0);

        // Update shadow intensity using Lambertian reflection formula
        shadowIntensity += ColorDBL(lamb, lamb, lamb);
    }

    return shadowIntensity;
}

//Function to call when we want to make recursion
ColorDBL Ray::reflectionRecursion(Ray& rayFromPixel, const int nmrOfReflections, const Scene& theScene){

    // Initialize variables to store information about the closest intersection
    float closestTobject = std::numeric_limits<float>::infinity();
    glm::vec3 closestIntersectionPoint;
    ColorDBL closestColor;
    std::shared_ptr<Object> closestObject = nullptr; // Added variable to store the closest object's surface

    // Loop through each object in the scene
    for (std::shared_ptr<Object> objectInTheRoom : theScene.getTheRoom()) {

        glm::vec3 intersectionPoint;

        if (objectInTheRoom->collision(rayFromPixel, intersectionPoint)) {

            // Initializes the end vertex
            rayFromPixel.endVertex = intersectionPoint;

            // Calculate t value for the intersection
            float t = glm::length(intersectionPoint - rayFromPixel.startVertex);

            // Check if this intersection is closer than the current closest one
            if (t < closestTobject) {
                closestTobject = t;
                closestIntersectionPoint = intersectionPoint;
                closestObject = objectInTheRoom; // Update the closest polygon

                // Goes through all lightsources in the scene (We only have one light)
                for (const Light& theLight : theScene.getLights()){
                    closestColor = closestObject->color_.mult(rayFromPixel.castShadowRay(closestObject, theLight, theScene.getTheRoom()));
                }

                // Initializes the end vertex if it is the closest
                this->endVertex = intersectionPoint;
            }
        }
    }

    // Will continue until nmrOfReflections is zero
    ColorDBL outLight;

    if (nmrOfReflections > 0) {
        glm::vec3 randDirection = randomGaussValue(closestObject->getNormal());
        Ray newReflectedRay(this->endVertex, randDirection);
        ColorDBL recursiveLight = reflectionRecursion(newReflectedRay, nmrOfReflections - 1, theScene);
        outLight = closestColor.add(recursiveLight); //* 0.3; <- why 0.3 (0_0)
        return outLight;
    }

    outLight = closestColor;
    return outLight;
}

glm::vec3 Ray::randomGaussValue(glm::vec3 normal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    double randomValueNorm = distribution(gen);
    while (randomValueNorm < -1.0 || randomValueNorm > 1.0) {
        randomValueNorm = distribution(gen);
    }
    std::uniform_real_distribution<double> distributionEven(-1.0, 1.0);

    float theta = 0.5 * 3.14f * randomValueNorm;
    float phi = 2.0f * 3.14f * distributionEven(gen);
    float x = std::sin(theta) * std::cos(phi);
    float y = std::sin(theta) * std::sin(phi);
    float z = std::cos(theta);
    glm::vec3 randDirection = normal + glm::vec3(x, y, z);
    return randDirection;   //NOT DONE
}
