#include "Camera.h"
#include <iostream>


Camera::Camera()
{
	up = glm::vec3(0.0,1.0,0.0);
	front = glm::vec3(0.0, 0.0, -1.0);
	position = glm::vec3(0.0, 1.0, 0.0);
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

void Camera::moveUp(float deltaTime) {
	glm::vec3 normalised = glm::normalize(up);
	position += normalised * (movementSpeed * deltaTime);
}

void Camera::look(double xpos, double ypos)
{
	if (!freezeRotation) {

		if (start) {
			lastxoff = xpos; //maybe refactor this out of global scope
			lastyoff = ypos; //this too
			start = false;
		}

		float x = xpos - lastxoff;
		float y = lastyoff - ypos;

		lastxoff = xpos;
		lastyoff = ypos;


		float xoff = x * lookSpeed;
		float yoff = y * lookSpeed;

		yaw += xoff;
		pitch += yoff;

		if (pitch > 89.0) {
			pitch = 89.0;
		}

		if (pitch < -89.0) {
			pitch = -89.0;
		}


		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front);
	}
}

void Camera::freeze()
{
	if (freezeRotation) {
		freezeRotation = false;
	}
	else {
		freezeRotation = true;
	}
}

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::vec3 Camera::getUp()
{
	return up;
}

glm::vec3 Camera::getFront()
{
	return front;
}

glm::mat4x4 Camera::getView()
{
	return view;
}

glm::mat4x4 Camera::getProjection()
{
	return projection;
}

glm::mat4x4 Camera::getRotation()
{
	return rotation;
}

float Camera::getFov()
{
	return fov;
}

void Camera::updateFov(float amount)
{
	if (!freezeRotation) {
		if (fov >= 1.0f) {//make sure fov does not go negative
			fov += amount;
		}
		else {
			fov = 1.0f;
		}
	}
}
