#include "../include/light.h"
#include "../include/polygon.h"
#include <random>

Light::Light(const Rectangle& surface, const glm::vec3& intensity)
    : surface_(surface), intensity_(intensity) {
            // Idea, take in vertices and then make a rectangle! using the vertices to get the position in the room!

    constantAttenuation_ = 1.0f;      // 1 - 0
    linearAttenuation_ = 0.1f;        // 0.1 - 0.01
    quadraticAttenuation_ = 0.01f;    // 0.01 - 0.001
    width_ = surface_.getWidth();
    height_ = surface_.getHeight();
    position_ = samplePoint();
}

glm::vec3 Light::samplePoint() const {
    // Randomly sample a point on the rectangular light source
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disU(-0.5f, 0.5f);
    std::uniform_real_distribution<float> disV(-0.5f, 0.5f);

    float u = disU(gen);
    float v = disV(gen);

    // Calculate the position on the rectangle based on width and height
    glm::vec3 position = glm::vec3(u * width_, v * height_, 0.0f);

    return position;
}

glm::vec3 Light::calculateIntensity(const glm::vec3& point) const {
    // Calculate the vector from the point on the surface to the light source
    glm::vec3 toLight = position_ - point;

    // Calculate the distance from the point to the light source
    float distance = glm::length(toLight);

    // Normalize the toLight vector
    toLight = glm::normalize(toLight);

    // Calculate the attenuation factor (you may need to tweak the constants)
    float attenuation = 1.0f / (constantAttenuation_ + linearAttenuation_ * distance + quadraticAttenuation_ * distance * distance);

    // Return the intensity, attenuated by the distance
    return intensity_ * attenuation;
}

bool Light::isPointOnLight(const glm::vec3& point) const {
    float halfWidth = 0.5f * width_;
    float halfHeight = 0.5f * height_;
    glm::vec3 delta = point - position_;
    return (
        point.x >= position_.x - halfWidth && point.x <= position_.x + halfWidth &&
        point.y >= position_.y - halfHeight && point.y <= position_.y + halfHeight
        );
}

glm::vec3 Light::getPosition() const {
    return position_;
}

glm::vec3 Light::getIntensity() const {
    return intensity_;
}

glm::vec3 Light::getNormal() const {
    // Get the normal direction of the light source (pointing towards the scene)
    return glm::vec3(0.0f, 0.0f, -1.0f);
}