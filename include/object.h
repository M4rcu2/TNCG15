#pragma once

#include "../include/glm/glm.hpp"
#include "../include/material.h"

class Object {
public:
    // Constructor
    Object();

    // Destructor (virtual, as objects may have derived classes)
    virtual ~Object();

    // Check for ray-object intersection and return the intersection point
    virtual bool intersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, float& t, glm::vec3& intersectionPoint) const = 0;

    // Get the object's material properties
    virtual Material getMaterial() const;

private:
    // Define properties common to all objects (e.g., material properties)

protected:
    // Define material properties here (e.g., color, reflectivity, transparency)

};