#pragma once
#include "light.h"
#include "polygon.h"
#include "colorDBL.h"
#include <random>

// Constructor
Light::Light(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const glm::vec3& intensity) {

    ColorDBL c = ColorDBL(intensity.x, intensity.y, intensity.z);
    surface_ = new Rectangle(p1, p2, p3, p4, c);
    intensity_ = intensity;

    //creates e1 and e2 along each side
    e1 = p2 - p1;
    e2 = p3 - p1;
    this->p1 = p1;
    area = glm::length(e1) * glm::length(e2);
}

glm::vec3 Light::getIntensity() const {
    return intensity_;
}

glm::vec3 Light::getNormal() const {
    // Get the normal direction of the light source (pointing towards the scene)
    return surface_->normal;
}

glm::vec3 Light::getRandomPointOnLight() const {

    float s = (float) rand()/RAND_MAX;
    float t = (float) rand()/RAND_MAX;
    glm::vec3 v1 = e1*s;
    glm::vec3 v2 = e2*t;

    //std::cout << (p1 + v1 + v2).x << " + " << (p1 + v1 + v2).y << " + " << (p1 + v1 + v2).z << std::endl;

    return p1+v1+v2;
}


