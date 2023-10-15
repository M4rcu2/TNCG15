#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include "colorDBL.h"


class Ray; // Forward declaration

// Base class for Polygon
class Polygon {
public:
 
    //Used to calculate if the ray intercepts the infinitaly large plane (should be used to get the point later)
    virtual bool IntersectPlane(const Ray& ray) const = 0;

    //Collision, bool for checking if it intersects
    virtual bool collision(const Ray& ray, glm::vec3& pointAtIntersection) const = 0;

    //returns the normal, should be used in the constructor
    virtual glm::vec3 getNormal() const = 0;

    //returns the color of the polygon
    ColorDBL color_;
    ColorDBL getColor() const {
        return color_;
    };

protected:
    Polygon() = default;
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

    bool IntersectPlane(const Ray& ray) const override; 
    bool collision(const Ray& ray, glm::vec3& pointAtIntersection) const override;
    glm::vec3 getNormal() const override;
    float getWidth() const;
    float getHeight() const;

    glm::vec3 recNormal;
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
    
    bool IntersectPlane(const Ray& ray) const override;
    bool collision(const Ray& ray, glm::vec3& pointAtIntersection) const override;
    glm::vec3 getNormal() const override;
    Triangle& operator=(const Triangle& other); //Copy constructor 
    
    glm::vec3 triNormal;
    glm::vec3 vertices[3]; // Defines vertices of the triangle
};


// tetrahedra subclass----------------------------------------------------------------------
class Tetrahedron {
public:
    Tetrahedron(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const ColorDBL c) {
        faces[0] = new Triangle(v0, v1, v2, c);
        faces[1] = new Triangle(v0, v2, v3, c);
        faces[2] = new Triangle(v0, v3, v1, c);
        faces[3] = new Triangle(v1, v3, v2, c);
    }
    glm::vec3 pointOnTetra(const Ray& ray);
    //Faces of the tetrahedra
    Triangle* faces[4];
};

// sphere subclass-------------------------------------------------------------------------- (Yeah spheres aren't polygons but it eases the calculations)
class Sphere {
public:
    Sphere(const double& r, const glm::vec3& center, const ColorDBL c) {
        radius = r;
        sphereCenter = center;
        sphereColor = c;
        
    }

    bool collision(const Ray& ray, glm::vec3& pointAtIntersection);
    
    double radius;
    glm::vec3 sphereCenter;
    ColorDBL sphereColor;
    glm::vec3 spheNormal;

};