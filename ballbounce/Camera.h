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

	void look(double xpos, double ypos);

	glm::vec3 getPosition();
	glm::vec3 getUp();
	glm::vec3 getFront();

	glm::mat4x4 getView();
	glm::mat4x4 getProjection();
	glm::mat4x4 getRotation();


private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::mat4x4 view;
	glm::mat4x4 rotation;
	glm::mat4x4 projection;
	float fov = 45.0f;
	float movementSpeed = 2.5;
	float lookSpeed = 0.1;
	float yaw;
	float pitch;
	float lastxoff;
	float lastyoff;
};

