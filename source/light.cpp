#include "../include/light.h"
#include "../include/polygon.h"
#include <random>

Light::Light(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const glm::vec3& intensity)
    : surface_(p1, p2, p3, p4, ColorDBL(intensity.x, intensity.y, intensity.z)) {

    constantAttenuation_ = 1.0f;
    linearAttenuation_ = 0.1f;
    quadraticAttenuation_ = 0.01f;

    intensity_ = intensity;
    width_ = surface_.getWidth();
    height_ = surface_.getHeight();
    position_ = samplePoint();

    //creates e1 and e2 along each side
        // e1 = position+width;
        // e2 = position+height;
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
    return surface_.normal;
}

glm::vec3 Light::getRandomPointOnLight() const {
    srand((unsigned) time(NULL));
    float x = (float) rand()/RAND_MAX;
    float y = (float) rand()/RAND_MAX;
    glm::vec3 v1 = e1*x;
    glm::vec3 v2 = e2*y;
    return v1+v2;
}


