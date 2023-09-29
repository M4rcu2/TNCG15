#pragma once
#include "../include/pixel.h"

Pixel::Pixel() : color(glm::vec3(0, 0, 0)) {}

void Pixel::setColor(const glm::vec3& color) {
    this->color = color;
}

glm::vec3 Pixel::getColor() const {
    return color;
}
