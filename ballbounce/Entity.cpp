#include "Entity.h"
#include <iostream>


Entity::Entity()
{
}

/*
	setup the entity
	@param position the position of this entity in the world
	@param scale the scale of this entity
	@param mass the mass of this entity
	@param typeVariable the typeVariable of this entity

*/
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

/*
	get the encoded type of this entity
	@return int type of entity 1 for ball 0 for plane
*/
int Entity::getType()
{
	return typeVariable;
}

/*
	get the position of this entity
	@return vec3 position
*/
glm::vec3 Entity::getPosition()
{
	return this->position;
}

/*
	apply a foce on this entity
	@param force force to apply on entity
*/
void Entity::applyForce(glm::vec3 force)
{
	if (kinematic) {
		this->force += force;
	}
}

/*
	udpate position of Entity
	@param deltaTime change in time
	@param freeFall true to take into account forces false otherwise
*/
void Entity::updatePosition(float deltaTime, bool freeFall)
{
	if (kinematic) {
		if (!freeFall) {
			this->acceleration = this->force / this->mass;
		}
		velocity = velocity + (acceleration * deltaTime);
		position += velocity;
		acceleration = glm::vec3(0);
	}
}

/*
	get the mass of this entity
	@return float mass
*/
float Entity::getMass() {
	return mass;
}

/*
	returns true if the entity is kinematic, false otherwise
	@return bool true for kinematic false otherwise
*/
bool Entity::isKinematic()
{
	return kinematic;
}

/*
	set the scale of this entity
	@param scale the scale amount
*/
void Entity::setScale(float scale)
{
	this->scale = scale;
}

/*
	get the scale factor of this entity
	@return float scale
*/
float Entity::getScale()
{
	return scale;
}

/*
	shift the position of this entity by some amount
	@param shiftAmount the amount to shift this entities position
*/
void Entity::shiftPosition(glm::vec3 shiftAmount)
{
	this->position += shiftAmount;
}

/*
	reset the position of this entity to its starting position
*/
void Entity::reset()
{
	position = startPoistion;
	velocity = glm::vec3(0.0);
	acceleration = glm::vec3(0.0);
	force = glm::vec3(0.0);
}

/*
	set the acceleration of this entity
	@param acc accerlation
*/
void Entity::setAcceleration(glm::vec3 acc)
{
	acceleration = acc;
}

/*
	set the position of this entity
	@param position position
*/
void Entity::setPosition(glm::vec3 position)
{
	this->position = position;
}

/*
	update the velocity of this entity if it is kinematic
	@param velocity velocity
*/
void Entity::updateVelocity(glm::vec3 velocity)
{
	if (kinematic) {
		this->velocity = velocity;
	}
}

/*
	get the velocity of this entity
	@return vec3 velocity
*/
glm::vec3 Entity::getVelocity()
{
	return velocity;
}
