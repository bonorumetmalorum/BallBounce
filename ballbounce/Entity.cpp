#include "Entity.h"
#include <iostream>


Entity::Entity()
{
}


Entity::~Entity()
{
}

int Entity::getType()
{
	return typeVariable;
}

glm::vec3 Entity::getPosition()
{
	return position;
}

//TODO check and see if this can be delete default that way it doesnt need to be implemented in non kinematic obj
void Entity::applyForce(glm::vec3 force)
{
	if (kinematic) {
		this->force += force;
	}
}

//TODO check and see if this can be delete default that way it doesnt need to be implemented in non kinematic obj
void Entity::updatePosition(float deltaTime, bool freeFall)
{
	if (kinematic) {
		if (!freeFall) {
			this->acceleration = this->force / this->mass;
			std::cout << "calculating acceleration by mass" << std::endl;
		}
		velocity = velocity + (acceleration * deltaTime);
		position += velocity;
		acceleration = glm::vec3(0);
		force = glm::vec3(0);
	}
}

float Entity::getMass() {
	return mass;
}

bool Entity::isKinematic()
{
	return kinematic;
}

void Entity::setScale(float scale)
{
	this->scale = scale;
}

float Entity::getScale()
{
	return scale;
}

void Entity::shiftPosition(glm::vec3 shiftAmount)
{
	this->position += shiftAmount;
}

void Entity::reset()
{
	position = startPoistion;
}

void Entity::setAcceleration(glm::vec3 acc)
{
	acceleration = acc;
}
