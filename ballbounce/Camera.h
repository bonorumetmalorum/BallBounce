#pragma once

#include "vec3.hpp"
#include "mat4x4.hpp"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp""

class Camera
{
public:
	Camera();

	~Camera();

	void moveForward(float amount);

	void moveBack(float amount);
	
	void moveLeft(float amount);
	
	void moveRight(float amount);

	void moveUp(float deltaTime);

	void look(double xpos, double ypos);

	void freeze();

	glm::vec3 getPosition();
	glm::vec3 getUp();
	glm::vec3 getFront();

	float getFov();
	void updateFov(float amount);

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	float fov = 45.0f;
	float movementSpeed = 2.5;
	float lookSpeed = 0.1;
	float yaw;
	float pitch;
	float lastxoff = 0;
	float lastyoff = 0;
	bool freezeRotation = false;
	bool start = true;
};

