#pragma once

#include "../include/glm/glm.hpp"
#include "../include/polygon.h"

//// Forward declaration
//class Rectangle;

class Light {
public:

    // Constructor
    Light(const Rectangle& position, const glm::vec3& intensity);

    // Randomly sample a point on the rectangular light source
    glm::vec3 samplePoint() const;

    // Calculate the intensity (color) of the light at a given point
    glm::vec3 calculateIntensity(const glm::vec3& point) const;

    // Check if a given point is on the light source
    bool isPointOnLight(const glm::vec3& point) const;

    // Getters for light properties
    glm::vec3 getPosition() const;
    glm::vec3 getIntensity() const;
    glm::vec3 getNormal() const;

private:
    glm::vec3 intensity_; // Intensity (color) of the light  
    glm::vec3 position_;
    Rectangle surface_;
    float constantAttenuation_;
    float linearAttenuation_ ;
    float quadraticAttenuation_ ;
    float width_;         // Width of the rectangle
    float height_;        // Height of the rectangle
};

