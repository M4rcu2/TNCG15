#pragma once

#include "glm/glm.hpp"

class Pixel {
public:
    Pixel();

    void setColor(const glm::vec3& color);
    glm::vec3 getColor() const;

private:
    glm::vec3 color;
};