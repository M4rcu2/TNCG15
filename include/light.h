#pragma once

#include "../include/glm/glm.hpp"

class Light {
public:

    // Constructor
    Light(const glm::vec3& position, float width, float height, const glm::vec3& intensity);

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
    
    glm::vec3 getRandomPointOnLight() const;    //gets a random point on light where we have to implement two e1 and e2 vectors for the ligth and add these new variables to the constructor to initialize.s

private:
    glm::vec3 position_;    // Position of the light source
    glm::vec3 intensity_; // Intensity (color) of the light   
    float width_;         // Width of the rectangle
    float height_;        // Height of the rectangle
    glm::vec3 e1;
    glm::vec3 e2;
};

