#pragma once

#include "../include/glm/glm.hpp"
#include "../include/polygon.h"

//// Forward declaration
//class Rectangle;

class Light {
public:

    // Constructor
    Light(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const glm::vec3& intensity) : surface_(new Rectangle{p1, p2, p3, p4, ColorDBL(intensity.x, intensity.y, intensity.z)}){
        
        constantAttenuation_ = 1.0f;
        linearAttenuation_ = 0.1f;
        quadraticAttenuation_ = 0.01f;
        intensity_ = intensity;

        //creates e1 and e2 along each side
        e1 = p1 - p2;
        e2 = p1 - p3;
    }

    // Getters for light properties
    glm::vec3 getIntensity() const;
    glm::vec3 getNormal() const;
    
    glm::vec3 getRandomPointOnLight() const;  //gets a random point on light where we have to implement two e1 and e2 vectors for the ligth and add these new variables to the constructor to initialize.s
    Polygon* surface_;

private:
    glm::vec3 intensity_; // Intensity (color) of the light  
    
    float constantAttenuation_;
    float linearAttenuation_ ;
    float quadraticAttenuation_ ;
    glm::vec3 e1;
    glm::vec3 e2;
};

