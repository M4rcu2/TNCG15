#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "../include/glm/glm.hpp"
#include "../include/ray.h"

//// 3D point for homogeneous coordinates
//class Point3D {
//public:
//    double x, y, z, w;  // Homogeneous coordinates (x, y, z, w)
//
//    // Constructor
//    Point3D(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}
//};
//
//// Base class for Polygon
//class Polygon {
//public:
//    virtual bool Intersect(const Ray& ray, Point3D& intersectionPoint) const = 0;
//};
//
//// Rectangle subclass----------------------------------------------------------------------
//class Rectangle : public Polygon {
//public:
//    Point3D vertices[4]; // Define vertices of the rectangle
//
//    const double EPSILON = 1e-6;
//
//    Rectangle(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4) {
//        vertices[0] = p1;
//        vertices[1] = p2;
//        vertices[2] = p3;
//        vertices[3] = p4;
//    }
//
//    bool Intersect(const Ray& ray, Point3D& intersectionPoint) const override {
//        // Compute the normal vector of the rectangle
//        glm::vec3 normal = CalculateNormal();
//
//        // Calculate the dot product of the ray direction and the normal
//        double dotProduct = glm::dot(ray.direction, normal);
//
//        // Check if the ray and the plane of the rectangle are parallel (or almost parallel)
//        if (fabs(dotProduct) < EPSILON) {
//            return false; // The ray is parallel to the rectangle, no intersection
//        }
//
//        // Compute the parameter t for the intersection point
//        double t = dot(rectangleOrigin - ray.origin, normal) / dotProduct;
//
//        // Check if the intersection point is in front of the ray's origin
//        if (t < 0) {
//            return false; // Intersection point is behind the ray
//        }
//
//        // Calculate the intersection point
//        intersectionPoint = ray.origin + t * ray.direction;
//
//        // Check if the intersection point is inside the rectangle
//        if (IsPointInsideRectangle(intersectionPoint)) {
//            return true; // Intersection point is inside the rectangle
//        }
//        else {
//            return false; // Intersection point is outside the rectangle
//        }
//    }
//};
//
//// Triangle subclass----------------------------------------------------------------------
//class Triangle : public Polygon {
//public:
//    Point3D vertices[3]; // Defines vertices of the triangle
//
//    // Constructor
//    Triangle(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
//        vertices[0] = p1;
//        vertices[1] = p2;
//        vertices[2] = p3;
//    }
//
//    // Implement the Intersect method for triangles
//    bool Intersect(const Ray& ray, Point3D& intersectionPoint) const override {
//        // Implement ray-triangle intersection logic here
//        // ...
//        return false; // Placeholder return
//    
//};

