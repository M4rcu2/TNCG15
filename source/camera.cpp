#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
    : position_(position), target_(target), up_(up)  {
}

void Camera::setPosition(const glm::vec3& position) {
    position_ = position;
}

void Camera::setTarget(const glm::vec3& target) {
    target_ = target;
}

void Camera::setUp(const glm::vec3& up) {
    up_ = up;
}

glm::vec3 Camera::getPosition() const {
    return position_;
}

glm::vec3 Camera::getTarget() const {
    return target_;
}

glm::vec3 Camera::getUp() const {
    return up_;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position_, target_, up_);
}

void Camera::setPerspectiveProjection(float fov, float aspectRatio, float nearClip, float farClip) {
    projectionMatrix_ = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projectionMatrix_;
}






