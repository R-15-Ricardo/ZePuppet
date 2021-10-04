#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
	public:
		Camera();
		Camera(float _pitch, float _yaw, glm::vec3 _position);
		void move(glm::vec3 velocity);
		void setPosition(glm::vec3 Position);
		void setTilt(float _pitch, float _yaw);
		void tilt(float _pitch, float _yaw);
		glm::mat4 getCamera();

	private:
		glm::vec3 Position;
		glm::vec3 Direction;
		float pitch;
		float yaw;
		//glm::mat4 MatCam;
};

