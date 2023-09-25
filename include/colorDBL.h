#pragma once

#include "../include/glm/glm.hpp"
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
    
private:
    double r, g, b;
};
