#include <iostream>
#include <vector>
#include <limits> // for std::numeric_limits

#include "../include/glm/glm.hpp"
#include "../include/colorDBL.h"
#include "../include/camera.h" 
#include "../include/ray.h" 
#include "../include/scene.h" 

int main() {
    // Creates the scene
    Scene theScene;

    // Adds the room
    theScene.addRoom();
    
    // Creates a camera placed in the room
    int imageWidth = 600;
    int imageHeight = 600;

    // Creates the camera with an image plane
    std::vector<std::vector<ColorDBL>> imagePlane(imageWidth, std::vector<ColorDBL>(imageHeight));
    Camera theCamera(glm::vec3(-1, 0, 0), imageWidth, imageHeight);
    theScene.addCamera(theCamera);

    // Add objects (e.g., spheres, triangles) to the scene
    //theScene.addPolygon(new Triangle(glm::vec3(9, 5, -4), glm::vec3(9, -5, -4), glm::vec3(9, 5, 4), ColorDBL(0.98, 0.51, 0.01)));


    // Adds a light to the scene
    Light* theLight = new Light(glm::vec3(9, -2, 4.999), glm::vec3(7, -2, 4.999), glm::vec3(9, 2, 4.999), glm::vec3(7, 2, 4.999), glm::vec3(1, 1, 1));
    theScene.addLight(theLight);
   
    // Loop through each pixel in the matrix and assigns the color -----------------------------------------------------
    for (int row = 0; row < imageWidth; ++row) {
        for (int col = 0; col < imageHeight; ++col) {

            // Calculate normalized device coordinates (NDC)
            float ndcX = (2.0f * row / static_cast<float>(imageWidth)) - 1.0f;
            float ndcY = 1.0f - (2.0f * col / static_cast<float>(imageHeight));

            // Create a ray with startpos at the eye and endpos at the camera plane
            Ray rayFromPixel = theCamera.castRay(ndcX, ndcY);

            // Initialize variables to store information about the closest intersection
            float closestT = std::numeric_limits<float>::infinity();
            glm::vec3 closestIntersectionPoint;
            ColorDBL closestColor;
            const Polygon* closestPolygon = nullptr; // Added variable to store the closest polygon

            // Loop through each polygon in the scene
            for (const Polygon* p : theScene.getTheRoom()) {

                glm::vec3 intersectionPoint = p->PointInPolygon(rayFromPixel);

                // If the ray intersects the polygon
                if (intersectionPoint != glm::vec3(-100, -100, -100)) {

                    // Calculate t value for the intersection
                    float t = glm::length(intersectionPoint - rayFromPixel.startVertex);

                    // Check if this intersection is closer than the current closest one
                    if (t < closestT) {
                        closestT = t;
                        closestIntersectionPoint = intersectionPoint;
                        closestColor = p->color_;
                        closestPolygon = p; // Update the closest polygon
                    }
                }

                
            }

            // If there is a valid intersection, calculate direct lighting contribution
            if (closestT != std::numeric_limits<float>::infinity()) {

                // Use the normal of the intersected polygon
                glm::vec3 theNormal = glm::normalize(closestPolygon->getNormal()); // Assuming getNormal() is a function in your Polygon class that returns the normal

                //std::cout << theNormal.x << " + " << theNormal.y << " + " << theNormal.z << std::endl;

                // Loop through each light in the scene
                for (const Light* light : theScene.getLights()) {
                    
                    // Check if the point on the surface is visible to the light source
                    if (!theScene.isShadowed(closestIntersectionPoint, light)) {

                        // Calculate the direction to the light source
                        glm::vec3 toLight = glm::normalize(light->getPosition() - closestIntersectionPoint); // Ensure to reverse the direction

                        // Calculate the diffuse reflection using Lambert's law
                        float diffuseFactor = glm::max(0.0f, glm::dot(theNormal, toLight));

                        //std::cout << diffuseFactor << std::endl;

                        // Calculate the intensity from the light source
                        glm::vec3 lightIntensity = light->calculateIntensity(closestIntersectionPoint);

                        // Update the color with the direct lighting contribution
                        closestColor.r += diffuseFactor * lightIntensity.x;
                        closestColor.g += diffuseFactor * lightIntensity.y;
                        closestColor.b += diffuseFactor * lightIntensity.z;
                    }
                }
            }

            // Assign the color of the closest intersection
            imagePlane[imageWidth - 1 - row][col] = closestColor;

        }
    }

    // Saves the rendered picture as a PNG -----------------------------------------------------------------------------
    const char* outputPath = "../outputImage/rendered_image.png";
    
    theCamera.renderAndSaveImage(outputPath, imageWidth, imageHeight, imagePlane);
    
    return 0;
}
