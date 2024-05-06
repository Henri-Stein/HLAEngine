#include "Transform.hpp"

Transform::Transform() :
	_position{0},
	_rotation{},
	_scale{1.0f, 1.0f, 1.0f}
{}

// Constructor from vectors
Transform::Transform(const glm::vec3& pos, const glm::vec3& eulerAngles, const glm::vec3& scale) :
	_position{pos},
	_rotation{eulerAngles},
	_scale{scale}
{}

// Constructor from scalar
Transform::Transform(const float& xPos,
	const float& yPos,
	const float& zPos,
	const float& pitch,
	const float& yaw,
	const float& roll,
	const float& xScale,
	const float& yScale,
	const float& zScale)
	:
	_position{xPos, yPos, zPos},
	_rotation{glm::vec3(pitch, yaw, roll)},
	_scale{xScale, yScale, zScale}
{}


glm::mat4 Transform::getModelMat() const
{
	return getTranslationMat() * getRotationMat() * getScaleMat();
}

glm::mat4 Transform::getTranslationMat() const
{
	return glm::translate(glm::mat4(1.f), _position);
}

glm::mat4 Transform::getRotationMat() const
{
	return glm::toMat4(_rotation);
}

glm::mat4 Transform::getScaleMat() const
{
	return glm::scale(glm::mat4(1.0f), _scale);
}

glm::vec3 Transform::getPosition() const
{
	return _position;
}

void Transform::setPosition(const glm::vec3& pos)
{
	_position = pos;
}

void Transform::setPosition(const float& x, const float& y, const float& z)
{
	_position = glm::vec3(x, y, z);
}

glm::vec3 Transform::getRotationEuler() const
{
	return glm::eulerAngles(_rotation);
}

float Transform::getPitch() const
{
	return glm::eulerAngles(_rotation).x;
}

float Transform::getYaw() const
{
	return glm::eulerAngles(_rotation).y;
}

float Transform::getRoll() const
{
	return glm::eulerAngles(_rotation).z;
}

void Transform::setRotation(const float& radians, const glm::vec3& direction)
{
	_rotation = glm::angleAxis(radians, glm::normalize(direction));
}


void Transform::setRotation(const glm::vec3& eulers)
{
	_rotation = glm::quat(eulers);
}

void Transform::rotate(const float& radians, const glm::vec3& direction)
{
	_rotation = glm::angleAxis(radians, direction) * _rotation;
}

void Transform::setRotation(const float& pitch, const float& yaw, const float& roll)
{
	_rotation = glm::quat(glm::vec3(pitch, yaw, roll));
}

glm::quat Transform::getRotationQuat() const
{
	return _rotation;
}

glm::vec3 Transform::getScale() const
{
	return _scale;
}

void Transform::setScale(const float& xScale, const float& yScale, const float& zScale)
{
	_scale = glm::vec3(xScale, yScale, zScale);
}

void Transform::setScale(const glm::vec3& scale)
{
	_scale = scale;
}