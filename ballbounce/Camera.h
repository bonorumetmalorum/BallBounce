#pragma once

#include "vec3.hpp"
#include "mat4x4.hpp"
#include <GLFW/glfw3.h>
#include "glm.hpp"

class Camera
{
public:
	Camera();

	~Camera();

	void moveForward(float amount);

	void moveBack(float amount);
	
	void moveLeft(float amount);
	
	void moveRight(float amount);

	void look(GLFWwindow * window, double xpos, double ypos);

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::mat4x4 view;
	glm::mat4x4 rotation;
	float fov = 45.0f;
	float movementSpeed = 2.0f;
	float lookSpeed = 2.0f;
	float yaw;
	float pitch;
	float lastxoff;
	float lastyoff;
};

