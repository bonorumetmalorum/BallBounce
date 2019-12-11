#include "Camera.h"
#include <iostream>


/*
	create a new camera instance
	@return Camera instance
*/
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

/*
	moves the camera forward
	@param deltaTime the change in time
*/
void Camera::moveForward(float deltaTime)
{
	position += (movementSpeed * deltaTime) * front;
}
/*
	moves the camera backward
	@param deltaTime the change in time
*/
void Camera::moveBack(float deltaTime)
{
	position -= (movementSpeed * deltaTime) * front;
}
/*
	moves the camera left
	@param deltaTime the change in time
*/
void Camera::moveLeft(float deltaTime)
{
	glm::vec3 normalised = glm::normalize(glm::cross(front, up));
	position -= normalised * (movementSpeed * deltaTime);
}
/*
	moves the camera right
	@param deltaTime the change in time
*/
void Camera::moveRight(float deltaTime)
{
	glm::vec3 normalised = glm::normalize(glm::cross(front, up));
	position += normalised * (movementSpeed * deltaTime);
}
/*
	moves the camera up (direction of world up)
	@param deltaTime the change in time
*/
void Camera::moveUp(float deltaTime) {
	glm::vec3 normalised = glm::normalize(up);
	position += normalised * (movementSpeed * deltaTime);
}

/*
	given the x and y coordinates of the mouse pointer, rotate the camera to look in that direction
	@param xpos x position of curosr
	@param ypos y position of cursor
*/
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

/*
	freeze and unfreeze the rotation of the camera
*/
void Camera::freeze()
{
	if (freezeRotation) {
		freezeRotation = false;
	}
	else {
		freezeRotation = true;
	}
}

/*
	get the current position of the camera
	@return vec3 camera position
*/
glm::vec3 Camera::getPosition()
{
	return position;
}

/*
	get the camera up vector
	@return vec3 up vector
*/
glm::vec3 Camera::getUp()
{
	return up;
}

/*
	get the cameras front vector
	@return vec3 front vector
*/
glm::vec3 Camera::getFront()
{
	return front;
}

/*
	get the cameras FoV
	@return float fov angle
*/
float Camera::getFov()
{
	return fov;
}


/*
	sets the fov with lower bound 1.0
	@parameter amount new fov
*/
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
