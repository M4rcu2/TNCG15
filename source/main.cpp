#include <iostream>
#include <vector>

#include "../include/glm/glm.hpp"
#include "../include/camera.h" 
#include "../include/ray.h" 
#include "../include/scene.h" 


int main() {
    
    // Creates a camera placed in the room
    Camera Camera(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1));

    // Define image width and height
    int imageWidth = 800;
    int imageHeight = 600;

    // Create a vector to store generated rays
    std::vector<Ray> rays;

    // Loop through each pixel on the image plane
    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {

            // Calculate normalized device coordinates (NDC)
            float ndcX = (2.0f * x / imageWidth) - 1.0f;
            float ndcY = 1.0f - (2.0f * y / imageHeight);

            // For orthographic projection, the ray direction is constant
            glm::vec3 rayDirection(0.0f, 0.0f, -1.0f); // Straight along the negative Z-axis

            // Create a ray with the camera position as the origin and the constant direction
            Ray ray(Camera.getPosition(), rayDirection);

            // Store the ray in the vector
            rays.push_back(ray);
        }
    }

    // Create a scene and add objects and lights to it
    Scene scene;

    // Add objects (e.g., spheres, triangles) to the scene
    

    // Adds a pointlight to the scene
    PointLight* light1 = new PointLight(glm::vec3(0, 0, 1), glm::vec3(1, 1, 1), 1.0f);
    scene.addLight(light1);

    // Loop through each ray and perform ray-object intersection tests
    for (const Ray& ray : rays) {
        // Find the closest intersection between the ray and objects in the scene
        // ...

        // If an intersection is found, calculate shading (e.g., diffuse, specular) for the point of intersection
        // ...

        // Accumulate the color contribution from lights, materials, and other shading effects
        // ...
    }

    // Now you have calculated the color for each pixel in the 'rays' vector.

    // Save the rendered image to a file (e.g., PNG, JPEG)
    // ...

    return 0;
    
}
