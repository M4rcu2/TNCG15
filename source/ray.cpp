#include "../include/ray.h"


Ray::Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color, Ray* prev, Ray* next)
: startVertex(start), direction(direction), previousRay(prev), nextRay(next), color(color)  {
    glm::normalize(direction); // Normalizes the direction vector
}

ColorDBL Ray::castShadowRay(const Polygon* fromPolygon, const Light* lightsource) {//Should change lightsource to a lightsource instead of polygon
    //implement function to see if there is an object in the way
    int nmrOfShadowrays = 5;

    for (int i = 0; i <= nmrOfShadowrays; i++) {

        glm::vec3 p = lightsource->getRandomPointOnLight();

        Ray castedShadowRay(p, glm::normalize(p - endVertex));

        //lightsource.surface_->PointInPolygon(castedShadowRay);

    }

    //The shadow ray
    /*Ray shadowRay(, (lightsource-> - pointOnSurface));
    
    //If the two surfaces normals are opposite they can shadow ray
    if(glm::dot(fromPolygon->normal, lightsource->normal) <=  0){
        //Add var for ray from surface to light, it has to be in the same direction (where will we put the ray on the surface? Do we need to put it on the surface?) The function below has to take in an ray that is pointing to the light, but it cannot be made since it will go through the surface then so we might have to do a variable and test if the ray goes into the surface?
        glm::vec3 pointOnLight = lightsource->PointInPolygon(rayfromsurface to light); //can they see eachother
        if(pointOnLight != glm::vec3(-100,-100,-100)){
            this->color = this->color.mult(lightsource->getIntensity());
        }
    }*/
    return this->color;
}
