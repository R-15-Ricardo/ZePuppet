#pragma once

#include <glm/glm.hpp>
#include <utility>

struct Ellipsoid {
		//Frame attributes
		glm::vec3 framePosition = glm::vec3(0.f,0.f,0.f);;
		glm::vec3 frameScale = glm::vec3(1.f,1.f,1.f);;
		glm::vec3 frameOrientation = glm::vec3(0.f,0.f,0.f);;
		
		//Object attributes (with respect to frame)
		glm::vec3 objectPosition = glm::vec3(0.f,0.f,0.f);
		glm::vec3 objectScale = glm::vec3(1.f,1.f,1.f);
		glm::vec3 objectOrientation = glm::vec3(0.f,0.f,0.f);

		//Only universal attribute god help me
		glm::vec4 color = glm::vec4(0.47f,0.64f,0.98f,1.f);
};

std::pair<int,int> genS2Mesh(double radius, int precision, float*& vertices, unsigned int*& indices);
//void printVertices(int precision, float* vertices);