#include <iostream>
#include <vector>

#include "../include/glm/glm.hpp"
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

    Camera theCamera(glm::vec3(-1, 0, 0), imageWidth, imageHeight);
    theScene.addCamera(theCamera);

    // Add objects (e.g., spheres, triangles) to the scene
    

    // Adds a light to the scene
    Light* theLight = new Light(glm::vec3(0, 0, 5), 4.0f, 4.0f, glm::vec3(1, 1, 1));
    theScene.addLight(theLight);
   
    // Creates a vector containing all normalized direction rays from each pixel
    std::vector<Ray> rays = theCamera.castRay();

    // Loop through each ray and perform ray-object intersection tests
    for (const Ray& ray : rays) {
        for(const Polygon* p : theScene.getTheRoom()){
            glm::vec3 checkPoint = p->PointInPolygon(ray);
            if(checkPoint != glm::vec3(-100,-100,-100)){
                //We should set the pixel value here//p->getColor()
            }
        }
        // Find the closest intersection between the ray and objects in the scene
        // ...

        // If an intersection is found, calculate shading (e.g., diffuse, specular) for the point of intersection
        // ...

        // Accumulate the color contribution from lights, materials, and other shading effects
        // ...
    }

    // Now you have calculated the color for each pixel in the 'rays' vector.

    // Saves the picture as a PNG
    const char* outputPath = "../outputImage/rendered_image.png";
    theCamera.renderAndSaveImage(outputPath, imageWidth, imageHeight);
    
    return 0;
}
