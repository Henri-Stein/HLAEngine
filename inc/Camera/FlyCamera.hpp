#ifndef FLY_CAMERA_H
#define FLY_CAMERA_H

#include "Camera.hpp"

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class FlyCamera : public Camera
{
public:
    // constructor with vectors
    FlyCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = DEFAULT_YAW, float pitch = DEFAULT_PITCH);

    // constructor with scalar values
    FlyCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(CameraMovement direction, float deltaTime) override;
};
#endif