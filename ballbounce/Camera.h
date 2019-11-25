#pragma once

#include "vec3.hpp"
#include "mat4x4.hpp"
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	~Camera();

	void updatePosition();

	void updateRotation();

private:
	glm::vec3 position;
	glm::mat4x4 view;
	glm::mat4x4 rotation;
	float fov = 45.0f;
	float movementSpeed = 2.0f;
	float rotationSpeed = 2.0f;
};

