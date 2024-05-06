#ifndef TRANSFORM_HPP
#define TRANSFORM_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


class Transform
{
public:
	Transform();

	// Constructor from vectors
	Transform(const glm::vec3& pos, const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));
	
	// Constructor from scalar
	Transform(const float& xPos,
			   const float& yPos, 
			   const float& zPos, 
			   const float& pitch, 
			   const float& yaw, 
			   const float& roll, 
			   const float& xScale, 
			   const float& yScale, 
			   const float& zScale);

	/*** Matrices related utility functions ***/
	glm::mat4 getModelMat() const;

	glm::mat4 getTranslationMat() const;
	glm::mat4 getRotationMat() const;
	glm::mat4 getScaleMat() const;

	/* Position related utility functions */
	glm::vec3 getPosition() const;
	void setPosition(const glm::vec3& pos);
	void setPosition(const float& x, const float& y, const float& z);

	/*** Rotation related utility functions ***/
	// Return euler angles as Pitch, Yaw and Roll (in this order). Result is expressed in radians
	glm::vec3 getRotationEuler() const;
	glm::quat getRotationQuat() const;
	// Return the rotation around the X-axis (pitch) in radians
	float getPitch() const;
	// Return the rotation around the Y-axis (yaw) in radians
	float getYaw() const;
	// Return the rotation around the Z-axis (roll) in radians
	float getRoll() const;

	void rotate(const float& radians, const glm::vec3& direction);

	void setRotation(const float& radians, const glm::vec3& direction);
	void setRotation(const glm::vec3& eulersRadians);
	void setRotation(const float& pitchRadians, const float& yawRadians, const float& rollRadians);

	/*** Scale related utility functions ***/
	glm::vec3 getScale() const;
	void setScale(const float& xScale, const float& yScale, const float& zScale);
	void setScale(const glm::vec3& scale);


private:
	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;
};

#endif