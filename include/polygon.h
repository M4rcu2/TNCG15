#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include "../include/glm/glm.hpp"
#include "../include/ray.h"

// 3D point for homogeneous coordinates
/*  Is this needed??
class Point3D {
public:
    // Constructor
    //Vad är _w? Vad ska vi använda den för???????????
    Point3D(double _x, double _y, double _z, double _w) : point(_x,_y,_z) {}
private:
    glm::vec3 point;
};*/

// Base class for Polygon
class Polygon {
public:
    //Used to calculate if the ray intercepts the infinitaly large plane (should be used to get the point later)
    virtual bool IntersectPlane(const Ray& ray, glm::vec3& intersectionPoint) const = 0;
    //This maybe need to be a vec3 to get the point of intersection but this function will calculate the point of intersection, firstly it should call intersectPlane so it doesn't need to calculate if the ray never go in that direction.
    virtual bool PointOfIntersection() const = 0;
    //returns the normal, should be used in the constructor
    virtual glm::vec3 getNormal() const = 0;
private:
    glm::vec3 planeNormal;
    const double EPSILON = 1e-6; //error margin i guess ;)
};

// Rectangle subclass----------------------------------------------------------------------
class Rectangle : public Polygon {
public:
    Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4) {
        recCorners[0] = p1;
        recCorners[1] = p2;
        recCorners[2] = p3;
        recCorners[3] = p4;
    }

    bool IntersectPlane(const Ray& ray, glm::vec3& intersectionPoint) const override {
        // Compute the normal vector of the rectangle
        glm::vec3 normal = getNormal();

        // Calculate the dot product of the ray direction and the normal
        double dotProduct = glm::dot(ray.direction, normal);

        // Check if the ray and the plane of the rectangle are parallel (or almost parallel)
        if (fabs(dotProduct) < EPSILON) {
            return false; // The ray is parallel to the rectangle, no intersection
        }

        // Compute the parameter t for the intersection point
        double t = dot(rectangleOrigin - ray.origin, normal) / dotProduct;

        // Check if the intersection point is in front of the ray's origin
        if (t < 0) {
            return false; // Intersection point is behind the ray
        }

        // Calculate the intersection point
        intersectionPoint = ray.origin + t * ray.direction;

        // Check if the intersection point is inside the rectangle
        if (IsPointInsideRectangle(intersectionPoint)) {
            return true; // Intersection point is inside the rectangle
        }
        else {
            return false; // Intersection point is outside the rectangle
        }
    }
private:
    glm::vec3 recCorners[4];
};

// Triangle subclass----------------------------------------------------------------------
class Triangle : public Polygon {
public:
    Point3D vertices[3]; // Defines vertices of the triangle

    // Constructor
    Triangle(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
    }

    // Implement the Intersect method for triangles
    bool Intersect(const Ray& ray, Point3D& intersectionPoint) const override {
        // Implement ray-triangle intersection logic here
        // ...
        return false; // Placeholder return
    }
};

