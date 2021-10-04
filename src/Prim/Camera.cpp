#include "Camera.hpp"

Camera::Camera()
{
	this->pitch = 0;
	this->yaw = -90.f;
	this->Position = glm::vec3(0.f,0.f,0.f);
}

Camera::Camera(float _pitch, float _yaw, glm::vec3 _position)
{
	if (-89.0f <= _pitch && _pitch <= 89.0)
		this->pitch = _pitch;
	else 
		this->pitch = 90.f;
	
	this->yaw = _yaw;
	this->Position = _position;
}

void Camera::move(glm::vec3 velocity)
{
	this->Position += velocity;
}

void Camera::setPosition(glm::vec3 Position)
{
	this->Position = Position;
}

void Camera::setTilt(float _pitch, float _yaw)
{
	if (-89.0f <= _pitch && _pitch <= 89.0)
		this->pitch = _pitch;
	else 
		this->pitch = 90.f;
	
	this->yaw = yaw;
}

void Camera::tilt(float _pitchOffset, float _yawOffset)
{
	this->pitch = (this->pitch <= 89.f) ? this->pitch + _pitchOffset : this->pitch;
	this->yaw += _yawOffset;
}

glm::mat4 Camera::getCamera()
{
	this->Direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	this->Direction.y = sin(glm::radians(pitch));
	this->Direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	glm::vec3 cameraFront = glm::normalize(Direction);
	glm::mat4 viewMatrix = glm::lookAt(Position, Position + cameraFront, glm::vec3(0.f,1.0f,0.f));
	return viewMatrix;
}