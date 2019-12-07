#include "Entity.h"
#include <iostream>


Entity::Entity()
{
}

Entity::Entity(glm::vec3 position, float scale, float mass, int typeVariable)
{
	this->position = position;
	this->startPoistion = position;
	this->scale = scale;
	this->mass = mass;
	this->typeVariable = typeVariable;
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
	return this->position;
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
			//std::cout << "calculating acceleration by mass" << std::endl;
		}
		velocity = velocity + (acceleration * deltaTime);
		position += velocity;
		acceleration = glm::vec3(0);
		//force = glm::vec3(0);
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
	std::cout << position.x << " " << position.y << " " << position.z << std::endl;
}

void Entity::reset()
{
	position = startPoistion;
	velocity = glm::vec3(0.0);
	acceleration = glm::vec3(0.0);
	force = glm::vec3(0.0);
}

void Entity::setAcceleration(glm::vec3 acc)
{
	acceleration = acc;
}

void Entity::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Entity::updateVelocity(glm::vec3 velocity)
{
	if (kinematic) {
		this->velocity = velocity;
	}
}
