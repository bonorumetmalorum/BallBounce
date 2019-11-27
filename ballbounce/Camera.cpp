#include "Camera.h"



Camera::Camera()
{
	up = glm::vec3(0.0,1.0,0.0);
	front = glm::vec3(0.0, 0.0, -1.0);
	yaw = -90.0f;
	pitch = 0.0f;
	lastxoff = 0.0f;
	lastyoff = 0.0f;
}


Camera::~Camera()
{
}

void Camera::moveForward(float deltaTime)
{
	position += (movementSpeed * deltaTime) * front;
}

void Camera::moveBack(float deltaTime)
{
	position -= (movementSpeed * deltaTime) * front;
}

void Camera::moveLeft(float deltaTime)
{
	glm::vec3 normalised = glm::normalize(glm::cross(front, up));
	position -= normalised * (movementSpeed * deltaTime);
}

void Camera::moveRight(float deltaTime)
{
	glm::vec3 normalised = glm::normalize(glm::cross(front, up));
	position += normalised * (movementSpeed * deltaTime);
}

void Camera::look(GLFWwindow * window, double xpos, double ypos)
{
	float xoff = xpos - lastxoff;
	float yoff = lastyoff - ypos;

	xoff = xoff * lookSpeed;
	yoff = yoff * lookSpeed;

	lastxoff = xoff;
	lastyoff = yoff;

	yaw += xoff;
	pitch += yoff;

	(pitch > 90.0) ? pitch = 90.0 : (pitch < -90.0) ? pitch = -90.0 : pitch = pitch;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
}
