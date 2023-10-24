#include "ray.h"
#include "polygon.h"
#include "scene.h"  //Tar in scene för att använda
#include <random>
#include <cmath>
#include <glm/gtc/random.hpp>

Ray::Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color, Ray* prev, Ray* next)
    : startVertex(start), direction(glm::normalize(direction)), previousRay(prev), nextRay(next), color(color) {
}

ColorDBL Ray::castShadowRay(const std::shared_ptr<Object>& fromObject, const Light& lightsource, const std::vector<std::shared_ptr<Object>>& allObjects) {

    // Creates a black color
    ColorDBL shadowIntensity = ColorDBL(0.0, 0.0, 0.0);

    // Number of shadow rays
    int nmrOfShadowrays = 3;

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

        double lamb = std::max(((v_1 * lightsource.area * M_PI * cosThetaX * (-cosThetaY)) / denominator), 0.0);

        // Update shadow intensity using Lambertian reflection formula
        shadowIntensity += ColorDBL(lamb, lamb, lamb);
    }
    ColorDBL a = shadowIntensity.divideComponents(nmrOfShadowrays/6.0f);
    std::cout<<"shadow values "<<a;
    
    if(a.r >=1 or a.g >= 1 or a.b>=1){
        std::cout<<"WHYYYYYYYY-----------------------"; //WHY DO WE GET LARGER THAN 1 In shadows???????-------------------
        std::cin.ignore();
    }
    return shadowIntensity.divideComponents(nmrOfShadowrays/6.0f);
}

//Function to call when we want to make recursion
ColorDBL Ray::reflectionRecursion(const int nmrOfReflections, const Scene& theScene){
    //std::cout<<"reflection called with ray as:\n"<<*this;
    //std::cout<<"\n\n new refecltion recurs called\n";
    //std::cout<<"THE RAY direction "<<glm::to_string(this->direction)<<" start "<< glm::to_string(this->startVertex)<< " end  "<<glm::to_string(this->endVertex)<<"\n";
    // Initialize variables to store information about the closest intersection
    float closestTobject = std::numeric_limits<float>::infinity();
    glm::vec3 closestIntersectionPoint;
    ColorDBL closestColor;
    std::shared_ptr<Object> closestObject = nullptr; // Added variable to store the closest object's surface

    // Loop through each object in the scene
    for (std::shared_ptr<Object> objectInTheRoom : theScene.getTheRoom()) {
        //std::cout<<"new shape check!\n";
        glm::vec3 intersectionPoint;// = glm::vec3(0,0,0);
        //std::cout<<"intersection point is: "<<glm::to_string(intersectionPoint)<<"\n";
        if (objectInTheRoom->collision(*this, intersectionPoint)) {
            //std::cout<<"collision done!!!\n";
            // Calculate t value for the intersection
            float t = abs(glm::length(intersectionPoint - this->startVertex));
            //std::cout<<"tt value "<<t<<"\n";
            
            // Check if this intersection is closer than the current closest one
            if (t < closestTobject) {
                //std::cout<<"new closest\n";
                closestTobject = t;
                closestIntersectionPoint = intersectionPoint;
                closestObject = objectInTheRoom; // Update the closest polygon
                // Initializes the end vertex
                this->endVertex = intersectionPoint;
                
                // Goes through all lightsources in the scene (We only have one light)
                for (const Light& theLight : theScene.getLights()){
                    //Adds 0.08 to ambient light.
                    ColorDBL shadowRayAndAmb = ColorDBL(0.08,0.08,0.08).add(this->castShadowRay(closestObject, theLight, theScene.getTheRoom()));
                    
                    closestColor = closestObject->color_.mult(shadowRayAndAmb); //CHECK THIS TOO; AND THEN A LITTLE BIT LOWER TOO AND ABOVE IN THE SHADOW SHIT
                }
                
                //std::cout<<"new closest objecT\n"<<*this;
            }
        }
    }
    if(closestObject == nullptr){
        return ColorDBL(2.0,2.0,2.0);
    }
    
    // Will continue until nmrOfReflections is zero
    ColorDBL outLight;
    ColorDBL recursiveLight;
    if(nmrOfReflections <= 0){
        return closestColor;
    }
    else if (nmrOfReflections > 0) {
        do{
            glm::vec3 randDirection = randomGaussValue(closestObject->getNormal());
            this->nextRay = new Ray(this->endVertex, randDirection);//newReflectedRay;
            recursiveLight = this->nextRay->reflectionRecursion(nmrOfReflections - 1, theScene);
        }while(recursiveLight.Equal(ColorDBL(2.0,2.0,2.0)));
        //Clear the next ray when done using it
        delete this->nextRay;
        this->nextRay = nullptr;

        double reflectiveness = 0.6f;
        /*outLight = closestColor.add(recursiveLight.mult(ColorDBL(reflectiveness,reflectiveness,reflectiveness)));
        return outLight.divideComponents(1.1);*/

        outLight = closestColor.add(recursiveLight.mult(reflectiveness));
        return outLight;
    }
}

glm::vec3 Ray::randomGaussValue(glm::vec3 normal){
    //Random generation
 std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);
    double randomValueNorm = distribution(gen);
    while (randomValueNorm < -1 || randomValueNorm > 1) {  //If random value is outside [-1,1]
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
    
    //std::cout<<"dot prodsuct: "<< glm::dot(randDirection, normal)<<"\n";
    if(glm::dot(randDirection, normal)<=0)  //UGLY SOLUTION
        randDirection = glm::vec3(-randDirection.x,-randDirection.y,-randDirection.z);
    //std::cout<<"dot prodsuct after: "<< glm::dot(randDirection, normal)<<"\n";
    //std::cout<<"randdirection : "<<glm::to_string(randDirection)<<"\n";
    return randDirection;
}
