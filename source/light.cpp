#include "light.h"

// Constructor
Light::Light(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const ColorDBL& intensity) {

    surface_ = Rectangle(p1, p2, p3, p4, intensity, 0);
    color_ = intensity;

    //creates e1 and e2 along each side
    e1 = p2 - p1;
    e2 = p3 - p1;
    this->p1 = p1;
    area = glm::length(e1) * glm::length(e2);
}

ColorDBL Light::getIntensity() const {
    return color_;
}

glm::vec3 Light::getNormal() const {
    // Get the normal direction of the light source (pointing towards the scene)
    //return surface_->normal;
    return glm::vec3(0,0,-1);
}

glm::vec3 Light::getRandomPointOnLight() const {

    float s = (float) rand()/RAND_MAX;
    float t = (float) rand()/RAND_MAX;
    glm::vec3 v1 = e1*s;
    glm::vec3 v2 = e2*t;

    return p1+v1+v2;
}


