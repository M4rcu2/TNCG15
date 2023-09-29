#include "../include/light.h"
#include <random>

glm::vec3 Light::getIntensity() const {
    return intensity_;
}

glm::vec3 Light::getNormal() const {
    // Get the normal direction of the light source (pointing towards the scene)
    return glm::vec3( 0, 0, -1);
}

glm::vec3 Light::getRandomPointOnLight() const {
    srand((unsigned) time(NULL));
    float x = (float) rand()/RAND_MAX;
    float y = (float) rand()/RAND_MAX;
    glm::vec3 v1 = e1*x;
    glm::vec3 v2 = e2*y;
    return v1+v2;
}


