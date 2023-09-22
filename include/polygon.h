#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include "../include/glm/glm.hpp"

#include "../include/ray.h"
class Ray; // Forward declaration

// Base class for Polygon
class Polygon {
public:
    const float errorMargin = 10e-4; //error margin i guess ;)
    
    //Calculate the point where we intersect the plane and then if it is in the polygon and returns that point
    virtual glm::vec3 PointInPolygon(const Ray& ray) const = 0;
    //Used to calculate if the ray intercepts the infinitaly large plane (should be used to get the point later)
    virtual bool IntersectPlane(const Ray& ray) const = 0;
    //returns the normal, should be used in the constructor
    virtual glm::vec3 getNormal() const = 0;
};

// Rectangle subclass----------------------------------------------------------------------
class Rectangle : public Polygon {
public:
    Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
        normal = getNormal();
    }
    glm::vec3 PointInPolygon(const Ray& ray) const override;
    glm::vec3 normal;
private:
    bool IntersectPlane(const Ray& ray) const override;
    glm::vec3 getNormal() const override;
    glm::vec3 vertices[4];
};

// Triangle subclass----------------------------------------------------------------------
class Triangle : public Polygon {
public:
    // Constructor
    Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        normal = getNormal();
    }
    // Implement the Intersect method for triangles
    glm::vec3 PointInPolygon(const Ray& ray) const override;
    glm::vec3 normal;
private:
    bool IntersectPlane(const Ray& ray) const override;
    glm::vec3 getNormal() const override;
    glm::vec3 vertices[3]; // Defines vertices of the triangle
};

