#pragma once

#include "../include/glm/glm.hpp"
//#include "../include/polygon.h"

//// Forward declaration
//class Rectangle; DO WE NEED FORWARD DECLERATION????
class Rectangle{
    
};
class Light {
public:
    // Constructor
    Light(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const ColorDBL& c) : 
    surface_(p1, p2, p3, p4,c),
    color(c)
    {
        //Rectangle(p1, p2, p3, p4,c);

        //creates e1 and e2 along each side
        e1 = p1 - p2;
        e2 = p1 - p3;
    }

    // Getters for light properties
    glm::vec3 getIntensity() const;
    glm::vec3 getNormal() const;
    
    glm::vec3 getRandomPointOnLight() const;  //gets a random point on light where we have to implement two e1 and e2 vectors for the ligth and add these new variables to the constructor to initialize.s
    Rectangle surface_;

private:
    ColorDBL color; // Intensity (color) of the light
    glm::vec3 e1;
    glm::vec3 e2;
};

