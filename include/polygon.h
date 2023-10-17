#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include "colorDBL.h"


class Ray; // Forward declaration

class Object {
public:
    //Collision, bool for checking if it intersects
    virtual bool collision(const Ray& ray, glm::vec3& pointAtIntersection) = 0;

    //returns the normal, should be used in the constructor
    virtual glm::vec3 getNormal() const = 0;

    //returns the color & the material of the polygon
    ColorDBL color_;
    std::string material_;
    
    ColorDBL getColor() const {
        return color_;
    };

    std::string getMaterial() const {
        return material_;
    };
};

// Base class for Polygon
class Polygon : public Object {
public:
 
    bool collision(const Ray& ray, glm::vec3& pointAtIntersection) override;

    glm::vec3 getNormal() const override;

    //Used to calculate if the ray intercepts the infinitaly large plane (should be used to get the point later)
    virtual bool IntersectPlane(const Ray& ray) const = 0;

    Polygon() = default;
};

// Rectangle subclass----------------------------------------------------------------------
class Rectangle : public Polygon {
public:
    Rectangle() = default;

    Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, ColorDBL color, std::string material) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
        recNormal = getNormal();
        color_ = color;
        material_ = material;
    }

    bool IntersectPlane(const Ray& ray) const override; 
    bool collision(const Ray& ray, glm::vec3& pointAtIntersection) override;
    glm::vec3 getNormal() const override;
    float getWidth() const;
    float getHeight() const;

    glm::vec3 recNormal;
    glm::vec3 vertices[4];
};

// Triangle subclass----------------------------------------------------------------------
class Triangle : public Polygon {
public:
    Triangle() = default;

    Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, ColorDBL color, std::string material) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        triNormal = getNormal();
        color_ = color;
        material_ = material;
    }
    
    bool IntersectPlane(const Ray& ray) const override;
    bool collision(const Ray& ray, glm::vec3& pointAtIntersection) override;
    glm::vec3 getNormal() const override;
    Triangle& operator=(const Triangle& other); //Copy constructor 
    
    glm::vec3 triNormal;
    glm::vec3 vertices[3]; // Defines vertices of the triangle
};

// tetrahedra subclass----------------------------------------------------------------------
class Tetrahedron : public Object {
public:
    Tetrahedron(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const ColorDBL color, std::string material) {
        faces[0] = std::make_shared<Triangle>(v0, v1, v2, color, material);
        faces[1] = std::make_shared<Triangle>(v0, v2, v3, color, material);
        faces[2] = std::make_shared<Triangle>(v0, v3, v1, color, material);
        faces[3] = std::make_shared<Triangle>(v1, v3, v2, color, material);
    }
    
    bool collision(const Ray& ray, glm::vec3& pointAtIntersection) override;

    glm::vec3 getNormal() const override;

    std::shared_ptr<Triangle> faces[4];
};

// sphere subclass-------------------------------------------------------------------------- (Yeah spheres aren't polygons but it eases the calculations)
class Sphere : public Object {
public:
    Sphere() = default;

    Sphere(const double& r, const glm::vec3& center, const ColorDBL color, std::string material) {
        radius = r;
        sphereCenter = center;
        color_ = color;
        material_ = material;
        spheNormal = getNormal();
    }

    bool collision(const Ray& ray, glm::vec3& pointAtIntersection) override;;

    glm::vec3 getNormal() const override;
    
    double radius;
    glm::vec3 sphereCenter;
    glm::vec3 spheNormal;
};
