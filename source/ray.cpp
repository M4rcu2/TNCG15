#include "ray.h"
#include "polygon.h"
#include "scene.h"  //Tar in scene för att använda
#include <glm/gtx/string_cast.hpp>  //print glm::vec
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

    const float EPSILON = 10e-3f;

    for (int i = 0; i < nmrOfShadowrays; i++) {

        double v_1 = 1.0;

        // Get a random point on the light source
        glm::vec3 pointOnLight = lightsource.getRandomPointOnLight();
        glm::vec3 pointOnObject = this->endVertex;
        glm::vec3 objectPoint = glm::vec3(0, 0, 0);

        // Calculate distances
        glm::vec3 di = (pointOnLight - pointOnObject);
        float di_distance = glm::length(di);
        float di_distance2 = std::numeric_limits<float>::max();

        // Create a shadow ray from the hit point to the light source
        Ray castedShadowRay(pointOnObject, glm::normalize(di));

        for (std::shared_ptr<Object> o : allObjects) { // Checks all polygons in the scene

            if (o != fromObject && o->collision(castedShadowRay, objectPoint)) { // if point hits something

                float newDistance = glm::length(objectPoint - pointOnObject) + EPSILON; // calculates the distance from the polygon to the intersectionpoint

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

        double lamb = std::max(((v_1 * lightsource.area * 3.1415f * cosThetaX * (-cosThetaY)) / denominator), 0.0);

        // Update shadow intensity using Lambertian reflection formula
        shadowIntensity += ColorDBL(lamb, lamb, lamb);
    }
    return shadowIntensity.divideComponents(nmrOfShadowrays/6.0f);
}

//Function to call when we want to make recursion
ColorDBL Ray::reflectionRecursion(Ray& rayFromPixel, const int nmrOfReflections, const Scene& theScene){
    
    // Initialize variables to store information about the closest intersection
    float closestTobject = std::numeric_limits<float>::infinity();
    glm::vec3 closestIntersectionPoint;
    ColorDBL closestColor;
    std::shared_ptr<Object> closestObject = nullptr; // Added variable to store the closest object's surface
    glm::vec3 intersectionPoint;

    // Will continue until nmrOfReflections is zero
    ColorDBL outLight;
    
    // Loop through each object in the scene
    for (std::shared_ptr<Object> objectInTheRoom : theScene.getTheRoom()) {

        if (objectInTheRoom->collision(rayFromPixel, intersectionPoint)) {
           
            // Calculate t value for the intersection
            float t = glm::length(intersectionPoint - rayFromPixel.startVertex);

            // Check if this intersection is closer than the current closest one
            if (t < closestTobject) {
                closestTobject = t;
                closestIntersectionPoint = intersectionPoint;
                closestObject = objectInTheRoom; // Update the closest polygon
       
                rayFromPixel.endVertex = intersectionPoint; // Initializes the end vertex
                
                // Goes through all lightsources in the scene (We only have one light)
                for (const Light& theLight : theScene.getLights()){

                    if (closestObject->getMaterial() == 1) { // Mirror

                        glm::vec3 d_i = this->direction;
                        glm::vec3 N = closestObject->getNormal();

                        glm::vec3 outDirection = d_i - 2.0f * glm::dot(d_i, N) * N;

                        Ray newReflectedRay(this->endVertex, outDirection);

                        ColorDBL reflectionColor = newReflectedRay.reflectionRecursion(newReflectedRay, (nmrOfReflections-1), theScene);

                        delete this->nextRay;
                        this->nextRay = nullptr;

                        closestColor = closestColor.add(reflectionColor);

                    } else if (closestObject->getMaterial() == 2) { // Lightsource
                        closestColor = theLight.getIntensity();
                        return closestColor;

                    } else {
                        closestColor = closestObject->color_.mult(ColorDBL(0.05, 0.05, 0.05).add(rayFromPixel.castShadowRay(closestObject, theLight, theScene.getTheRoom())));   //(color added so shadows become(0.1,0.1,0.1)}
                    }        
                }
                
                // Initializes the end vertex if it is the closest
                this->endVertex = intersectionPoint;
            }
        }
    }

    if (nmrOfReflections > 0) {

        glm::vec3 randDirection = randomGaussValue(closestObject->getNormal());

        this->nextRay = new Ray(this->endVertex, randDirection); //newReflectedRay;

        ColorDBL recursiveLight = this->nextRay->reflectionRecursion(*this->nextRay, (nmrOfReflections - 1), theScene);

        delete this->nextRay;
        this->nextRay = nullptr;

        outLight = closestColor.add(recursiveLight);
        return outLight;
    }

    outLight = closestColor;
    
    return outLight;
}

glm::vec3 Ray::randomGaussValue(glm::vec3 normal){
    //Random generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);
    double randomValueNorm = distribution(gen);
    while (randomValueNorm < -0.95 || randomValueNorm > 0.95) {  //If random value is outside [-1,1]
        randomValueNorm = distribution(gen);
    }
    std::uniform_real_distribution<double> distributionEven(-1.0, 1.0); //Even distrubution [-1,1]

    //polar coord. for normal and generated direction
    float thetaNormal = std::atan2(normal.y, normal.x);
    float phiNormal = std::acos(normal.z/ (std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z)));

    float theta = 2.0f * 3.14f * distributionEven(gen);
    float phi = 0.5f * 3.14f * randomValueNorm;
    
    float thetaOut = theta + thetaNormal;
    float phiOut = phi + phiNormal;
    
    float x = std::sin(phiOut) * std::cos(thetaOut);
    float y = std::sin(phiOut) * std::sin(thetaOut);
    float z = std::cos(phiOut);
    glm::vec3 randDirection = glm::normalize(glm::vec3(x,y,z));
    
    if(glm::dot(randDirection, normal)<=0)
        randDirection = glm::vec3(-randDirection.x,-randDirection.y,-randDirection.z);
    return randDirection;
}


