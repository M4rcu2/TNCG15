#pragma once

#include "glm/glm.hpp"

class Material {
public:

    // Default constructor
    Material();

    // Constructor with parameters
    Material(const glm::vec3& color, float ambient, float diffuse, float specular, float shininess);

    // Get and set color
    glm::vec3 getColor() const;
    void setColor(const glm::vec3& color);

    // Get and set ambient
    float getAmbient() const;
    void setAmbient(float ambient);

    // Get and set diffuse
    float getDiffuse() const;
    void setDiffuse(float diffuse);

    // Get and set specular
    float getSpecular() const;
    void setSpecular(float specular);

    // Get and set shininess
    float getShininess() const;
    void setShininess(float shininess);

private:
    glm::vec3 color_;    // Material color (RGB)
    float ambient_;      // Ambient reflection coefficient
    float diffuse_;      // Diffuse reflection coefficient
    float specular_;     // Specular reflection coefficient
    float shininess_;    // Shininess (specular exponent)
};