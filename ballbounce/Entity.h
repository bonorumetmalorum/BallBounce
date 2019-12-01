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

	virtual void applyForce(glm::vec3 force);
	virtual void updatePosition(float deltaTime);

	bool isKinematic();


private:

	float angle;

protected:
	glm::vec3 position;
	float scale = 1.0;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 force;
	float mass = 1.0;
	int typeVariable;
	bool kinematic = false;
};

/*
	this will keep track of the transformation matrices for this entity
	will implement a draw method to allow for convenient rendering
	will maintain its position
*/