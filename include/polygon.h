#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include "../include/colorDBL.h"
#include "../include/glm/glm.hpp"

#include "../include/ray.h"
class Ray; // Forward declaration

// Rectangle subclass----------------------------------------------------------------------
class Rectangle{
public:
    Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, ColorDBL color) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
        recNormal = getNormal();
        color_ = color;
    }
    glm::vec3 PointInPolygon(const Ray& ray) const;
    glm::vec3 recNormal;
    float getWidth() const;
    float getHeight() const;
    glm::vec3 getNormal() const;
    Rectangle& operator=(const Rectangle &other);
    ColorDBL color_;
    glm::vec3 vertices[4];
    ColorDBL getColor() const {
        return color_;
    };
private:
    bool IntersectPlane(const Ray& ray) const;
    const float errorMargin = 10e-4f; //error margin i guess ;)
    
};

// Triangle subclass----------------------------------------------------------------------
class Triangle{
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
    glm::vec3 PointInPolygon(const Ray& ray) const;
    glm::vec3 triNormal;
    ColorDBL color_;
    glm::vec3 vertices[3]; // Defines vertices of the triangle
    ColorDBL getColor() const {
        return color_;
    };
private:
    bool IntersectPlane(const Ray& ray) const;
    glm::vec3 getNormal() const;
    const float errorMargin = 10e-4f; //error margin i guess ;)
};

