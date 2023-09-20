#include <iostream>
#include <vector>

#include "../include/glm/glm.hpp"
#include "../include/camera.h" 
#include "../include/ray.h" 
#include "../include/scene.h" 

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb/stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb/stb/stb_image.h"

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
    Scene theScene;

    // Add objects (e.g., spheres, triangles) to the scene
    

    // Adds a pointlight to the scene
    PointLight* light1 = new PointLight(glm::vec3(0, 0, 1), glm::vec3(1, 1, 1), 1.0f);
    theScene.addLight(light1);

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

    // Specify the output file path (e.g., "rendered_image.png")
    const char* outputPath = "../outputImage/rendered_image.png";

    // Create an array to store the image data
    unsigned char* imageData = new unsigned char[3 * imageWidth * imageHeight];

    int index = 0;

    // Loop through each pixel and populate the imageData array
    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            // Calculate the color for the pixel (x, y) and store it in imageData
            // Assuming you have computed the color in your ray tracing loop, you would set the RGB values accordingly
            // For example, assuming color is represented as glm::vec3
            glm::vec3 pixelColor = glm::vec3(1,0,0); // Compute the color for this pixel
            imageData[index++] = static_cast<unsigned char>(pixelColor.r * 255); // Red
            imageData[index++] = static_cast<unsigned char>(pixelColor.g * 255); // Green
            imageData[index++] = static_cast<unsigned char>(pixelColor.b * 255); // Blue
        }
    }

    // Save the image to a file using STB Image
    stbi_write_png(outputPath, imageWidth, imageHeight, 3, imageData, imageWidth * 3);

    // Clean up allocated memory
    delete[] imageData;

    return 0;
    
}
