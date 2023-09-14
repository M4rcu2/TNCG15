#pragma once
#include "../include/glm/glm.hpp"
#include <vector>

class ColorDBL {
public:
    ColorDBL(double red, double green, double blue) : r(red), g(green), b(blue) {}//Constructor
    
    void changeColor(const double& red, const double& green, const double& blue);//Change color function
    
    std::vector<double> getColor();//rerturns a vector with rgb
    
private:
    double r, g, b;
};
