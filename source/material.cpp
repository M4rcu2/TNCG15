#include "../include/material.h"

Material::Material() {
    // Default constructor initializes properties to reasonable defaults
    color_ = glm::vec3(0.8f, 0.8f, 0.8f); // Default color is gray
    ambient_ = 0.2f;
    diffuse_ = 0.8f;
    specular_ = 0.0f;
    shininess_ = 1.0f;
}

Material::Material(const glm::vec3& color, float ambient, float diffuse, float specular, float shininess) {
    color_ = color;
    ambient_ = ambient;
    diffuse_ = diffuse;
    specular_ = specular;
    shininess_ = shininess;
}

glm::vec3 Material::getColor() const {
    return color_;
}

float Material::getAmbient() const {
    return ambient_;
}

float Material::getDiffuse() const {
    return diffuse_;
}

float Material::getSpecular() const {
    return specular_;
}

float Material::getShininess() const {
    return shininess_;
}

void Material::setColor(const glm::vec3& color) {
    color_ = color;
}

void Material::setAmbient(float ambient) {
    ambient_ = ambient;
}

void Material::setDiffuse(float diffuse) {
    diffuse_ = diffuse;
}

void Material::setSpecular(float specular) {
    specular_ = specular;
}

void Material::setShininess(float shininess) {
    shininess_ = shininess;
}