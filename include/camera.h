#pragma once

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ray.h"
#include "pixel.h"

class Camera {
public:
    Camera(const glm::vec3& eye, int imageWidth, int imageHeight);

    glm::vec3 getPos();

    Ray castRay(float pixelX, float pixelY);

    void renderAndSaveImage(const char* outputPath, int imageWidth, int imageHeight, std::vector<std::vector<ColorDBL>> matrix);

private:
    glm::vec3 eye_;
    glm::vec3 c1, c2, c3, c4;
    int imageWidth_;
    int imageHeight_;
};
