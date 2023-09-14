#pragma once

#include "../include/glm/glm.hpp"

class PointLight {
public:

    // Constructor
    PointLight(const glm::vec3& position, const glm::vec3& color, float intensity);

    // Getters for light properties
    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;
    float getIntensity() const;

private:
    glm::vec3 position_;    // Position of the light source
    glm::vec3 color_;       // Color of the light (RGB)
    float intensity_;       // Intensity of the light
};
