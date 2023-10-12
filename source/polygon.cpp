#pragma once

#include "polygon.h"
#include "ray.h"


// Rectangle subclass----------------------------------------------------------------------
glm::vec3 Rectangle::PointInPolygon(const Ray& ray) const{

    bool isOnPlane = IntersectPlane(ray);

    if(isOnPlane){
        glm::vec3 s = ray.startVertex;
        glm::vec3 d = ray.direction;
        glm::vec3 v = vertices[0];
        glm::vec3 c1 = vertices[1]-v;
        glm::vec3 c2 = vertices[2]-v;
        float t = glm::dot((v-s),recNormal)/glm::dot(d,recNormal);
        glm::vec3 intersectionPoint = s + t*d;

        //a and b criterion
        float a = glm::dot((intersectionPoint-v),c1)/glm::dot(c1,c1);
        float b = glm::dot((intersectionPoint-v),c2)/glm::dot(c2,c2);
        if(a>=0 && a<=1 && b>=0 && b<=1){
            return intersectionPoint + recNormal*errorMargin;
        }
    }
    glm::vec3 notOnPlane(-100,-100,-100);//Vector for when we do not intersect with the rectangle
    return notOnPlane;
}

// Is point obstructed by another object?
bool Rectangle::IsPointObstructed(const Ray& ray, glm::vec3& intersectionPoint) const {
    bool isOnPlane = IntersectPlane(ray);

    if (isOnPlane) {
        glm::vec3 s = ray.startVertex;
        glm::vec3 d = ray.direction;
        glm::vec3 v = vertices[0];
        glm::vec3 c1 = vertices[1] - v;
        glm::vec3 c2 = vertices[2] - v;
        float t = glm::dot((v - s), recNormal) / glm::dot(d, recNormal);
        intersectionPoint = s + t * d;

        // a and b criterion
        float a = glm::dot((intersectionPoint - v), c1) / glm::dot(c1, c1);
        float b = glm::dot((intersectionPoint - v), c2) / glm::dot(c2, c2);
        if (a >= 0 && a <= 1 && b >= 0 && b <= 1) {
            intersectionPoint = intersectionPoint + recNormal * errorMargin;
            return true;
        }
    }

    return false;
}

bool Rectangle::IntersectPlane(const Ray& ray) const{
    //Calculate if the normal of the infinitally large plane is opposoite direction of the ray to know if the ray goes away from the plane or not
    //Dot product calculation
    float dotProd = glm::dot(recNormal, ray.direction);
    //Is dot product positive, negative or zero?
    if(dotProd < 0){
        return true;//The ray and normal are opposite direction
    }
    else{
        return false;//Not opposite direction
    } 
}
//Calculate the normal and normalizes it before returning
glm::vec3 Rectangle::getNormal() const{
    glm::vec3 edge1 = vertices[1]-vertices[0];
    glm::vec3 edge2 = vertices[2]-vertices[0];
    glm::vec3 normal = glm::cross(edge1, edge2);
    normal = glm::normalize(normal);
    return normal;
}

// Implementations for new Rectangle methods
float Rectangle::getWidth() const {
    // Assuming vertices[1] and vertices[0] are adjacent edges of the rectangle
    return glm::length(vertices[1] - vertices[0]);
}

float Rectangle::getHeight() const {
    // Assuming vertices[2] and vertices[0] are adjacent edges of the rectangle
    return glm::length(vertices[2] - vertices[0]);
}

// Triangle subclass----------------------------------------------------------------------
glm::vec3 Triangle::PointInPolygon(const Ray& ray) const{
    bool isOnPlane = IntersectPlane(ray);
    if(isOnPlane){
        glm::vec3 E1 = vertices[1]-vertices[0];
        glm::vec3 E2 = vertices[2]-vertices[0];
        glm::vec3 T = ray.startVertex-vertices[0];
        glm::vec3 D = ray.direction;
        glm::vec3 P = glm::cross(D, E2);
        glm::vec3 Q = glm::cross(T, E1);
        //float t = dot(Q,E2)/dot(P,E1);
        float u = dot(P,T)/dot(P,E1);
        float v = dot(Q,D)/dot(P,E1);
        //implement intersectionPoint
        glm::vec3 intersectionPoint = (1-u-v)*vertices[0] + u*vertices[1] + v*vertices[2];
        if(u>=0 && v>=0 && u+v<=1){
            return intersectionPoint + triNormal*errorMargin;
        }
    }
    glm::vec3 notOnPlane(-100,-100,-100); //Vector for when we do not intersect with the triangle
    return notOnPlane;
}

// Is point obstructed by another object?
bool Triangle::IsPointObstructed(const Ray& ray, glm::vec3& intersectionPoint) const {
    bool isOnPlane = IntersectPlane(ray);

    if (isOnPlane) {
        glm::vec3 s = ray.startVertex;
        glm::vec3 d = ray.direction;
        glm::vec3 v = vertices[0];
        glm::vec3 c1 = vertices[1] - v;
        glm::vec3 c2 = vertices[2] - v;
        float t = glm::dot((v - s), triNormal) / glm::dot(d, triNormal);
        intersectionPoint = s + t * d;

        // a and b criterion
        float a = glm::dot((intersectionPoint - v), c1) / glm::dot(c1, c1);
        float b = glm::dot((intersectionPoint - v), c2) / glm::dot(c2, c2);
        if (a >= 0 && a <= 1 && b >= 0 && b <= 1) {
            intersectionPoint = intersectionPoint + triNormal * errorMargin;
            return true;
        }
    }

    return false;
}

//Function to know if the ray intersects the triangle (or more like "does it come from the right direction")
bool Triangle::IntersectPlane(const Ray &ray) const{
    //Calculate if the normal of the infinitally large plane is opposoite direction of the ray to know if the ray goes away from the plane or not
    //Dot product calculation
    float dotProd = glm::dot(triNormal, ray.direction);
    //Is dot product positive, negative or zero?
    if(dotProd < 0){
        return true;//Opposite direction for normal of the triangle and the ray
    }
    else{
        return false; //Not opposite direction
    }
}
//Calculate the normal and normalizes it before returning
glm::vec3 Triangle::getNormal() const{
    glm::vec3 edge1 = vertices[1]-vertices[0];
    glm::vec3 edge2 = vertices[2]-vertices[0];
    glm::vec3 normal = glm::cross(edge1, edge2);
    normal = glm::normalize(normal);
    return normal;
}
