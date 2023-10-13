#include <iostream>
#include <vector>
#include <limits> // for std::numeric_limits

#include "glm/glm.hpp"
#include "colorDBL.h"
#include "camera.h" 
#include "ray.h" 
#include "scene.h" 

int main() {
    // Creates the scene
    Scene theScene;

    // Adds the room
    theScene.addRoom();
    
    // Creates a camera placed in the room
    int imageWidth = 600;
    int imageHeight = 600;
    
    //Number of reflections the ray can do
    int nmrOfReflections = 2;

    // Creates the camera with an image plane
    std::vector<std::vector<ColorDBL>> imagePlane(imageWidth, std::vector<ColorDBL>(imageHeight));
    Camera theCamera(glm::vec3(-1, 0, 0), imageWidth, imageHeight);
    theScene.addCamera(theCamera);

    // Add objects (e.g., spheres, triangles) to the scene
    theScene.addPolygon(new Triangle(glm::vec3(10, 3, 0), glm::vec3(10, -3, 0), glm::vec3(3, 3, 2), ColorDBL(0.98, 0.51, 0.01)));

    // Adds a light to the scene
    Light theLight = Light(glm::vec3(-2, -2, 5), glm::vec3(-2, 2, 5), glm::vec3(2, -2, 5), glm::vec3(2, 2, 5), glm::vec3(1, 1, 1));
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
            for (Polygon* p : theScene.getTheRoom()) {

                glm::vec3 intersectionPoint = p->PointInPolygon(rayFromPixel);

                // If the ray intersects the polygon
                if (intersectionPoint != glm::vec3(-100, -100, -100)) {

                    // Initializes the end vertex
                    rayFromPixel.endVertex = intersectionPoint;

                    ColorDBL obtainedLight = rayFromPixel.castShadowRay(p,theLight,theScene.getTheRoom());

                    // Calculate t value for the intersection
                    float t = glm::length(intersectionPoint - rayFromPixel.startVertex);

                    // Check if this intersection is closer than the current closest one
                    if (t < closestT) {
                        closestT = t;
                        closestIntersectionPoint = intersectionPoint;
                        closestColor = p->color_.mult(obtainedLight);
                        closestPolygon = p; // Update the closest polygon
                    }
                }
            }

            //std::cout << closestColor.r << " + " << closestColor.g << " + " << closestColor.b << std::endl;

            // Assign the color of the closest intersection
            imagePlane[imageWidth - 1 - row][col] = closestColor;

        }
    }

    // Saves the rendered picture as a PNG -----------------------------------------------------------------------------
    const char* outputPath = "rendered_image.png";
    
    theCamera.renderAndSaveImage(outputPath, imageWidth, imageHeight, imagePlane);
    
    return 0;
}
