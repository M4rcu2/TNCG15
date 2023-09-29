#include "../include/light.h"
#include <random>

Light::Light(const glm::vec3& position, float width, float height, const glm::vec3& intensity)
: position_(position), intensity_(intensity), width_(width), height_(height) {
        //creates e1 and e2 along each side
        e1 = position+width;
        e2 = position+height;
    }

glm::vec3 Light::samplePoint() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-0.5f, 0.5f);
    float u = dis(gen) * width_;
    float v = dis(gen) * height_;
    return position_ + glm::vec3(u, v, 0.0f);
}

glm::vec3 Light::calculateIntensity(const glm::vec3& point) const {
    //Needs work
    return intensity_;
}

bool Light::isPointOnLight(const glm::vec3& point) const {
    
    float halfWidth = 0.5f * width_;
    float halfHeight = 0.5f * height_;
    glm::vec3 delta = point - position_;
    return (
        -halfWidth <= delta.x && delta.x <= halfWidth &&
        -halfHeight <= delta.y && delta.y <= halfHeight
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

glm::vec3 Light::getRandomPointOnLight() const {
    srand((unsigned) time(NULL));
    float x = (float) rand()/RAND_MAX;
    float y = (float) rand()/RAND_MAX;
    glm::vec3 v1 = e1*x;
    glm::vec3 v2 = e2*y;
    return v1+v2;
}


