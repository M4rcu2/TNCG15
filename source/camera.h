#pragma once

#include "../include/glm/glm.hpp"

class Camera {
public:

    // Constructor
    Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) : position_(position), target_(target), up_(up) {}

    // Set functions
    void setPosition(const glm::vec3& position) {
        position_ = position;
    }

    void setTarget(const glm::vec3& target) {
        target_ = target;
    }

    void setUp(const glm::vec3& up) {
        up_ = up;
    }

    // Get functions
    glm::vec3 getPosition() const {
        return position_;
    }

    glm::vec3 getTarget() const {
        return target_;
    }

    glm::vec3 getUp() const {
        return up_;
    }

    // Get the view matrix
    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position_, target_, up_);
    }

private:
    glm::vec3 position_;
    glm::vec3 target_;
    glm::vec3 up_;
};