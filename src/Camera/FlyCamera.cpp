#include "Camera/FlyCamera.hpp"
#include <iostream>

// constructor with vectors
FlyCamera::FlyCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : 
    Camera{ position, up, yaw, pitch }
{}

// constructor with scalar values
FlyCamera::FlyCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
    Camera{ posX, posY, posZ, upX, upY, upZ, yaw, pitch }
{}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void FlyCamera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = _speed * deltaTime;
    if (direction == FORWARD)
        _position += _front * velocity;
    if (direction == BACKWARD)
        _position -= _front * velocity;
    if (direction == LEFT)
        _position -= _right * velocity;
    if (direction == RIGHT)
        _position += _right * velocity;
}