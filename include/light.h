#pragma once

#include "../include/glm/glm.hpp"
#include "../include/polygon.h"
#include "../include/colorDBL.h"

// forward declaration
class Rectangle;

// Forward declaration
class ColorDBL;

class Light {
public:

    // Constructor
    Light(Rectangle* surface, const glm::vec3& intensity) : surface_(surface), intensity_(intensity) {
       
        //creates e1 and e2 along each side
        /*e1 = p1 - p2;
        e2 = p1 - p3;*/
    }

    // Getters for light properties
    glm::vec3 getIntensity() const;
    glm::vec3 getNormal() const;
    glm::vec3 getRandomPointOnLight() const;  //gets a random point on light where we have to implement two e1 and e2 vectors for the ligth and add these new variables to the constructor to initialize.s
    

private:
    Rectangle* surface_;
    glm::vec3 intensity_; // Intensity (color) of the light  
    glm::vec3 e1;
    glm::vec3 e2;    
};

