#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include "../include/colorDBL.h"
#include "../include/glm/glm.hpp"

#include "../include/ray.h"
class Ray; // Forward declaration

// Base class for Polygon
class Polygon {
public:
    const float errorMargin = 10e-4f; //error margin i guess ;)
    
    //Calculate the point where we intersect the plane and then if it is in the polygon and returns that point
    virtual glm::vec3 PointInPolygon(const Ray& ray) const = 0;
    //Used to calculate if the ray intercepts the infinitaly large plane (should be used to get the point later)
    virtual bool IntersectPlane(const Ray& ray) const = 0;
    //returns the normal, should be used in the constructor
    virtual glm::vec3 getNormal() const = 0;
    //returns the color of the polygon
    ColorDBL color_;
    ColorDBL getColor() const {
        return color_;
    };
};

// Rectangle subclass----------------------------------------------------------------------
class Rectangle : public Polygon {
public:
    Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, ColorDBL color) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
        recNormal = getNormal();
        color_ = color;
    }
    glm::vec3 PointInPolygon(const Ray& ray) const override;
    glm::vec3 recNormal;
    float getWidth() const;
    float getHeight() const;
    glm::vec3 getNormal() const override;
private:
    bool IntersectPlane(const Ray& ray) const override;
    
    glm::vec3 vertices[4];
};

// Triangle subclass----------------------------------------------------------------------
class Triangle : public Polygon {
public:
    // Constructor
    Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, ColorDBL color) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        triNormal = getNormal();
        color_ = color;
    }
    // Implement the Intersect method for triangles
    glm::vec3 PointInPolygon(const Ray& ray) const override;
    glm::vec3 triNormal;
private:
    bool IntersectPlane(const Ray& ray) const override;
    glm::vec3 getNormal() const override;
    glm::vec3 vertices[3]; // Defines vertices of the triangle
};

