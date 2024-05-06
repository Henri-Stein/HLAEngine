#include "Camera/Camera.hpp"
#include <iostream>

// constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
    _position(position),
    _front(glm::vec3(0.0f, 0.0f, -1.0f)),
    _worldUp(up),
    _yaw(yaw),
    _pitch(pitch),
    _speed(DEFAULT_SPEED),
    _mouseSensitivity(DEFAULT_SENSITIVITY),
    _zoom(DEFAULT_ZOOM)
{
    updateCameraVectors();
}

// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
    _position(posX, posY, posZ),
    _worldUp(upX, upY, upZ),
    _yaw(yaw),
    _pitch(pitch),
    _front(glm::vec3(0.0f, 0.0f, -1.0f)),
    _speed(DEFAULT_SPEED),
    _mouseSensitivity(DEFAULT_SENSITIVITY),
    _zoom(DEFAULT_SPEED)
{
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(_position, _position + _front, _up);
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
    xOffset *= _mouseSensitivity;
    yOffset *= _mouseSensitivity;

    _yaw += xOffset;
    _pitch += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yOffset)
{
    _zoom -= (float)yOffset;
    if (_zoom < 1.0f)
        _zoom = 1.0f;
    if (_zoom > MAX_ZOOM)
        _zoom = MAX_ZOOM;
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    _right = glm::normalize(glm::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _up = glm::normalize(glm::cross(_right, _front));
}