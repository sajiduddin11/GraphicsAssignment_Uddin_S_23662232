#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>  //GLFW functions and types

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f)
{
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

void Camera::processKeyboard(GLFWwindow* window, float deltaTime)  // Update the function signature
{
    float velocity = movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}



void Camera::processMouseScroll(float yOffset)
{
    zoom -= yOffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::calculateCameraVectors()
{
    front = glm::vec3(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch));
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::cross(right, front);
}

glm::mat4 Camera::getThirdPersonViewMatrix(glm::vec3 target)
{
    glm::vec3 offset = glm::vec3(0.0f, 2.0f, 6.0f); // height & distance behind player
    glm::vec3 camPos = target - front * offset.z + glm::vec3(0.0f, offset.y, 0.0f);
    return glm::lookAt(camPos, target, worldUp);
}
