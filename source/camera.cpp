#pragma once
#include "camera.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Camera::Camera(const glm::vec3& eye, int imageWidth, int imageHeight)
    : eye_(eye), imageWidth_(imageWidth), imageHeight_(imageHeight) {
    c1 = glm::vec3(0,-1,-1);
    c2 = glm::vec3(0, 1, -1);
    c3 = glm::vec3(0, 1, 1);
    c4 = glm::vec3(0, -1, 1);
}

glm::vec3 Camera::getPos() {
    return eye_;
}

Ray Camera::castRay(float pixelX, float pixelY) {

    // Calculates the ray direction (Normalized)
    glm::vec3 rayDirection = glm::normalize(glm::vec3(0, pixelX,pixelY) - eye_);

    // Initializes the ray
    Ray ray(eye_, rayDirection);

    return ray;
}



void Camera::renderAndSaveImage(const char* outputPath, int imageWidth, int imageHeight, std::vector<std::vector<ColorDBL>> matrix) {

    // Create an array to store the image data
    unsigned char* imageData = new unsigned char[3 * imageWidth * imageHeight];

    int index = 0;

    // Loop through each pixel and populate the imageData array
    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {

            ColorDBL pixelColor = matrix[x][y];

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









