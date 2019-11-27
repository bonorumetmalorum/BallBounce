#pragma once

#include "vec3.hpp"
#include "mat4x4.hpp"

class Entity
{
public:
	Entity();
	~Entity();

	virtual void draw() = 0;

private:
	glm::vec3 position;
	glm::mat4x4 translation;
	glm::mat4x4 scale;
};

/*
	this will keep track of the transformation matrices for this entity
	will implement a draw method to allow for convenient rendering
	will maintain its position
*/