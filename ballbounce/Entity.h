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
	glm::vec3 translation;
	glm::vec3 scale;
	float angle;
};

/*
	this will keep track of the transformation matrices for this entity
	will implement a draw method to allow for convenient rendering
	will maintain its position
*/