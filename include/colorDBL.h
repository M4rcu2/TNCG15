#pragma once

#include "../include/glm/glm.hpp"
#include <vector>

class ColorDBL {
public:
    // Default constructor
    ColorDBL() : r(0.0), g(0.0), b(0.0) {}

    // Constructor
    ColorDBL(float red, float green, float blue) : r(red), g(green), b(blue) {}
    
    // Change color function
    void changeColor(const float& red, const float& green, const float& blue);
    
    // Returns a vector with rgb
    std::vector<float> getColor();
    
    // Method to add two colors
    ColorDBL add(const ColorDBL& otherColor);

    // Method to multiply two colors
    ColorDBL mult(const ColorDBL& otherColor);

    // += operator for adding colors
    ColorDBL& operator+=(const ColorDBL& other);

    float r, g, b;

private:
    
};
