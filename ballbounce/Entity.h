#pragma once

#include "vec3.hpp"
#include "mat4x4.hpp"

class Entity
{
public:
	Entity();
	~Entity();

	virtual void draw() = 0;

	int getType();

	glm::vec3 getPosition();

private:

	float angle;

protected:
	glm::vec3 position;
	glm::vec3 translation;
	glm::vec3 scale;
	int typeVariable;
};

/*
	this will keep track of the transformation matrices for this entity
	will implement a draw method to allow for convenient rendering
	will maintain its position
*/