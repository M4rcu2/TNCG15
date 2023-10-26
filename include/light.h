#pragma once

#include "glm/glm.hpp"
#include "polygon.h"
#include "colorDBL.h"
#include <random>

class Rectangle;

class Light {
public:
    // Constructor
    Light(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const ColorDBL& intensity);

    // Getters for light properties
    ColorDBL getIntensity() const;
    glm::vec3 getNormal() const;
    
    glm::vec3 getRandomPointOnLight() const;  //gets a random point on light where we have to implement two e1 and e2 vectors for the ligth and add these new variables to the constructor to initialize.s
    Rectangle surface_;
    double area;

private:
    ColorDBL color_; // Intensity (color) of the light  
    glm::vec3 p1;
    glm::vec3 e1;
    glm::vec3 e2;
    
};

