#include <iostream>
#include <vector>

#include "../include/glm/glm.hpp"
#include "../include/camera.h" 
#include "../include/ray.h"   

int main() {


    int main() {
        // Create a camera with appropriate parameters
        Camera Camera();

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
                Ray ray(camera.getPosition(), rayDirection);

                // Store the ray in the vector
                rays.push_back(ray);
            }
        }

        // Now, you have a vector of rays, and you can use them for ray tracing.

        // ... (Ray tracing code)

        // ... (Image saving code)

        return 0;
}
