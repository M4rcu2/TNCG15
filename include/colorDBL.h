#pragma once

#include "glm/glm.hpp"
#include <iostream>
#include <vector>

class ColorDBL {
public:
    // Default constructor
    ColorDBL() : r(0.0), g(0.0), b(0.0) {}

    // Constructor
    ColorDBL(double red, double green, double blue) : r(red), g(green), b(blue) {}
    
    // Change color function
    void changeColor(const double& red, const double& green, const double& blue);
    
    // Returns a vector with rgb
    std::vector<double> getColor();
    
    // Method to add two colors
    ColorDBL add(const ColorDBL& otherColor);

    // Method to multiply two colors
    ColorDBL mult(const ColorDBL& otherColor);
    ColorDBL mult(const double mult);

    // Method to subtract two colors
    ColorDBL subtract(const ColorDBL& otherColor);

    // -= operator for subtracting colors
    ColorDBL& operator-=(const ColorDBL& other);

    // += operator for adding colors
    ColorDBL& operator+=(const ColorDBL& other);
    
    //Color divider
    ColorDBL divideComponents(double divisor) const {
        if(divisor <= 0){
            return ColorDBL(1,0,1);
        }
        return ColorDBL(r / divisor, g / divisor, b / divisor);
    }
    
    //print for color
    friend std::ostream& operator<<(std::ostream& os, const ColorDBL& color) {
        os << " RGB(" << color.r << ", " << color.g << ", " << color.b << ")\n";
        return os;
    }
    bool Equal(const ColorDBL& other) {
        return (r == other.r) && (g == other.g) && (b == other.b);
    }
    
    double r, g, b;
    
    
};
