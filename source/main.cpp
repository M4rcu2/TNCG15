#include <iostream>
#include <vector>
#include <limits> // for std::numeric_limits
#include <chrono> // for timing

#include "glm/glm.hpp"
#include "colorDBL.h"
#include "camera.h" 
#include "ray.h" 
#include "scene.h" 
#include <glm/gtx/string_cast.hpp>  //to string for vec

double randomizeEpsilon() {
    double min = 0.0004;
    double max = 0.001;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(gen);
}

int main() {
    // Creates the scene
    Scene theScene;
    
    // Adds the room
    theScene.addRoom();
    
    // Creates a camera placed in the room
    int imageWidth = 1200;
    int imageHeight = 1200;

    // Material definitons
    int standard = 0;
    int mirror = 1;
    
    // Number of reflections the ray can do
    int nmrOfReflections = 1;
    int samples = 200;

    // Create a time point to measure the rendering time
    auto start = std::chrono::high_resolution_clock::now();

    // Creates the camera with an image plane
    std::vector<std::vector<ColorDBL>> imagePlane(imageWidth, std::vector<ColorDBL>(imageHeight));
    Camera theCamera(glm::vec3(-1, 0, 0), imageWidth, imageHeight);
    theScene.addCamera(theCamera);

    // Adds objects to the scene
    theScene.addSphere(Sphere(1.0,glm::vec3(10, 0, -4),ColorDBL(0.0, 0.6, 0.6),standard));
    theScene.addSphere(Sphere(1.25, glm::vec3(0, -1.5, -3), ColorDBL(0.4, 0.1, 0.6), standard));
    theScene.addTetra(Tetrahedron(glm::vec3(6, -4, 1), glm::vec3(4, -2, -4), glm::vec3(4,-4,-4), glm::vec3(7, -2, -4), ColorDBL(0.98, 0.51, 0.01), standard));
    //theScene.addTetra(Tetrahedron(glm::vec3(9, 0, 3), glm::vec3(10, 2, -1), glm::vec3(8, -1, -1), glm::vec3(8, -3, -1), ColorDBL(0.4, 0.1, 0.6), standard));

    // Adds a light to the scene
    //Light theLight = Light(glm::vec3(-2, -2, 4.999), glm::vec3(-2, 2, 4.999), glm::vec3(2, -2, 4.999), glm::vec3(2, 2, 4.999), ColorDBL(1.0, 1.0, 1.0)); // Original light
    Light theLight = Light(glm::vec3(6, -1, 4.8), glm::vec3(4, -1, 4.8), glm::vec3(6, 1, 4.8), glm::vec3(4, 1, 4.8), ColorDBL(1.0, 1.0, 1.0));
    
    theScene.addLight(theLight);

    
    // Loop through each pixel in the matrix and assigns the color -----------------------------------------------------
    for (int row = 0; row < imageWidth; ++row) {

        std::cout << row << " of " << imageWidth << " complete, procentage: " << floor(100*(float)row/(float)imageWidth) << " % \n";

        for (int col = 0; col < imageHeight; ++col) {

            ColorDBL closestColor = ColorDBL(0,0,0);

            for(int n = 0; n < samples; ++n){

                // Calculate normalized device coo rdinates (NDC)
                float ndcX = (2.0f * row / static_cast<float>(imageWidth)) - 1.0f + randomizeEpsilon();
                float ndcY = 1.0f - (2.0f * col / static_cast<float>(imageHeight)) + randomizeEpsilon();
                
                // Create a ray with startpos at the eye and endpos at the camera plane
                Ray rayFromPixel = theCamera.castRay(ndcX, ndcY);
                
                //There will be a function here that we call with the ray, it's starting point aka from the camera and then it will calculate the light in a specific pixel.
                closestColor = closestColor.add(rayFromPixel.reflectionRecursion(rayFromPixel, nmrOfReflections, theScene));
            }
            // Assign the color of the closest intersection
            imagePlane[imageWidth - 1 - row][col] = closestColor.divideComponents(samples);
        }
    }

    // Saves the rendered picture as a PNG -----------------------------------------------------------------------------
    const char* outputPath = "../outputImage/rendered_image.png"; // For Marcus (Windows)
    //const char* outputPath = "rendered_image.png"; // For Filip (Mac)
    
    theCamera.renderAndSaveImage(outputPath, imageWidth, imageHeight, imagePlane);

    // Measure the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Calculate the rendering time in minutes and seconds
    int minutes = static_cast<int>(std::chrono::duration_cast<std::chrono::minutes>(elapsed).count());
    int seconds = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(elapsed).count()) - (minutes * 60);

    std::cout << "Rendering equation calculation took " << minutes << " minutes and " << seconds << " seconds." << std::endl;
    
    return 0;
}
