#include "../include/colorDBL.h"

void ColorDBL::changeColor(const double& newRed, const double& newGreen, const double& newBlue){
    r = newRed;
    g = newGreen;
    b = newBlue;
}

std::vector<double> ColorDBL::getColor(){
    return  std::vector<double>{r,g,b};
}

// += operator for adding colors
ColorDBL& ColorDBL::operator+=(const ColorDBL& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}
