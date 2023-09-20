#include "../include/light.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float intensity) {
    position_ = position;
    color_ = color;
    intensity_ = intensity;
}

glm::vec3 PointLight::getPosition() const {
    return position_;
}

glm::vec3 PointLight::getColor() const {
    return color_;
}

float PointLight::getIntensity() const {
    return intensity_;
}