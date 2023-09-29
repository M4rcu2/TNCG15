#include "../include/colorDBL.h"

void ColorDBL::changeColor(const double& newRed, const double& newGreen, const double& newBlue){
    r = newRed;
    g = newGreen;
    b = newBlue;
}

std::vector<double> ColorDBL::getColor(){
    return  std::vector<double>{r,g,b};
}

ColorDBL ColorDBL::add(const ColorDBL& otherColor) {
    return ColorDBL(r + otherColor.r, g + otherColor.g, b + otherColor.b);
}

ColorDBL ColorDBL::mult(const ColorDBL& otherColor) {
    return ColorDBL(r * otherColor.r, g * otherColor.g, b * otherColor.b);
}
