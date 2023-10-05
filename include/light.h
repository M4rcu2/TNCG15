#pragma once

#include "glm/glm.hpp"

// Forward declaration
class Polygon;

class Light {
public:
    // Constructor
    Light(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const glm::vec3& intensity);

    // Getters for light properties
    glm::vec3 getIntensity() const;
    glm::vec3 getNormal() const;
    
    glm::vec3 getRandomPointOnLight() const;  //gets a random point on light where we have to implement two e1 and e2 vectors for the ligth and add these new variables to the constructor to initialize.s
    Rectangle surface_;

private:
    ColorDBL color; // Intensity (color) of the light
    glm::vec3 e1;
    glm::vec3 e2;
};

