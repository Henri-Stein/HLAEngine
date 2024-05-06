#include "Camera/FPSCamera.hpp"

// constructor with vectors
FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
	Camera{ position, up, yaw, pitch }
{}

// constructor with scalar values
FPSCamera::FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
	Camera{ posX, posY, posZ, upX, upY, upZ, yaw, pitch }
{}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void FPSCamera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = _speed * deltaTime;
    if (direction == FORWARD)
        _position += glm::normalize(glm::vec3(_front.x, 0.0f, _front.z)) * velocity;
    if (direction == BACKWARD)
        _position -= glm::normalize(glm::vec3(_front.x, 0.0f, _front.z)) * velocity;
    if (direction == LEFT)
        _position -= glm::normalize(glm::vec3(_right.x, 0.0f, _right.z)) * velocity;
    if (direction == RIGHT)
        _position += glm::normalize(glm::vec3(_right.x, 0.0f, _right.z)) * velocity;
}