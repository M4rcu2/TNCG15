#pragma once

class Camera {
public:
    // Constructor
    Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

    // Sets position of the camera
    void setPosition(const glm::vec3& position);

    // Sets target direction
    void setTarget(const glm::vec3& target);

    // Sets up direction
    void setUp(const glm::vec3& up);

    // Gets the position
    glm::vec3 getPosition() const;

    // Gets the target direction
    glm::vec3 getTarget() const;

    // Gets the up direction
    glm::vec3 getUp() const;

    // Get the view matrix
    glm::mat4 getViewMatrix() const;

    // Set the projection matrix for perspective projection
    void setPerspectiveProjection(float fov, float aspectRatio, float nearClip, float farClip);

    // Get the projection matrix
    glm::mat4 getProjectionMatrix() const;

    // Renders the image to a png
    void renderAndSaveImage(const char* outputPath, int imageWidth, int imageHeight);

private:

    // Variables
    glm::vec3 position_;
    glm::vec3 target_;
    glm::vec3 up_;
    glm::mat4 projectionMatrix_ = glm::mat4(1.0f);
    
};