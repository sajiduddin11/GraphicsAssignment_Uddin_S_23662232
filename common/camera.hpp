// camera.hpp
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f, float pitch = 0.0f);

    void processKeyboard(GLFWwindow* window, float deltaTime);

    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void processMouseScroll(float yOffset);
    glm::mat4 getViewMatrix();
    void updateCameraVectors();

    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // Euler angles
// Camera Euler angles
    float yaw = glm::radians(-90.0f);
    float pitch = 0.0f;
    float roll = 0.0f;

    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    void calculateCameraVectors();
};

#endif