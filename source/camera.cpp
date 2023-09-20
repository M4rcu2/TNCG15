#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/camera.h"
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb/stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb/stb/stb_image.h"

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

void Camera::renderAndSaveImage(const char* outputPath, int imageWidth, int imageHeight) {

    // Create an array to store the image data
    unsigned char* imageData = new unsigned char[3 * imageWidth * imageHeight];

    int index = 0;

    // Loop through each pixel and populate the imageData array
    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            // Calculate the color for the pixel (x, y) and store it in imageData (NEEDS TO CHANGE!!!)
            // Assuming you have computed the color in your ray tracing loop, you would set the RGB values accordingly
            // For example, assuming color is represented as glm::vec3
            glm::vec3 pixelColor = glm::vec3(y, 0, x); // Compute the color for this pixel


            imageData[index++] = static_cast<unsigned char>(pixelColor.r * 255); // Red
            imageData[index++] = static_cast<unsigned char>(pixelColor.g * 255); // Green
            imageData[index++] = static_cast<unsigned char>(pixelColor.b * 255); // Blue
        }
    }

    // Save the image to a file using STB Image
    stbi_write_png(outputPath, imageWidth, imageHeight, 3, imageData, imageWidth * 3);
    std::cout << "Rendered file located at: " + static_cast<std::string>(outputPath) << std::endl << std::endl;
    
    // Clean up allocated memory
    delete[] imageData;
}






