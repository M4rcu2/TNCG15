#include <iostream>
#include <vector>

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

    // Creates a 2D matrix
    std::vector<std::vector<ColorDBL>> pixelMatrix(imageWidth, std::vector<ColorDBL>(imageHeight));

    Camera theCamera(glm::vec3(-1, 0, 0), imageWidth, imageHeight);
    theScene.addCamera(theCamera);

    // Add objects (e.g., spheres, triangles) to the scene
    

    // Adds a light to the scene
    Light* theLight = new Light(glm::vec3(0, 0, 5), 4.0f, 4.0f, glm::vec3(1, 1, 1));
    theScene.addLight(theLight);
   
    // Loop through each pixel in the matrix-------------------------------------------------------------------------
    for (int row = 0; row < imageWidth; ++row) {
        for (int col = 0; col < imageHeight; ++col) {
            // Calculate normalized device coordinates (NDC)
            float ndcX = (2.0f * row / static_cast<float>(imageWidth)) - 1.0f;
            float ndcY = 1.0f - (2.0f * col / static_cast<float>(imageHeight));

            // Create a ray with startpos at the eye and endpos at the camera plane
            Ray rayFromPixel = theCamera.getRay(ndcX, ndcY);

            for (const Polygon* p : theScene.getTheRoom()) {

                glm::vec3 checkPoint = p->PointInPolygon(rayFromPixel);

                //std::cout << p->color_.r << " + " << p->color_.g << " + " << p->color_.b << std::endl;

                if (checkPoint != glm::vec3(-100, -100, -100)) {
                    //We should set the pixel value here//p->getColor()
                    
                    //std::cout << "Intercetion! Color: " << p->color_.r << " + " << p->color_.g << " + " << p->color_.b << std::endl;

                    pixelMatrix[row][col] = p->color_;
                    break;
                }
            }
        }
    }

    // Now you have calculated the color for each pixel in the 'rays' vector.

    // Saves the picture as a PNG
    const char* outputPath = "../outputImage.png";
    
    theCamera.renderAndSaveImage(outputPath, imageWidth, imageHeight, pixelMatrix);
    
    return 0;
}
