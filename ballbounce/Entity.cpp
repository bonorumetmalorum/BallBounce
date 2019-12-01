#include "Entity.h"



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
void Entity::updatePosition(float deltaTime)
{
	if (kinematic) {
		acceleration = force / mass;
		velocity = velocity + (acceleration * deltaTime);
		position += velocity;
		//std::cout << position.x << " " << position.y << " " << position.z << std::endl;
		acceleration = glm::vec3(0);
		force = glm::vec3(0);
	}
}

bool Entity::isKinematic()
{
	return kinematic;
}
