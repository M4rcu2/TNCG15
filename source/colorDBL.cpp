#include "../include/colorDBL.h"

void ColorDBL::changeColor(const float& newRed, const float& newGreen, const float& newBlue){
    r = newRed;
    g = newGreen;
    b = newBlue;
}

std::vector<float> ColorDBL::getColor(){
    return  std::vector<float>{r,g,b};
}

// += operator for adding colors
ColorDBL& ColorDBL::operator+=(const ColorDBL& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

ColorDBL ColorDBL::add(const ColorDBL& otherColor) {
    return ColorDBL(r + otherColor.r, g + otherColor.g, b + otherColor.b);
}

ColorDBL ColorDBL::mult(const ColorDBL& otherColor) {
    return ColorDBL(r * otherColor.r, g * otherColor.g, b * otherColor.b);
}
