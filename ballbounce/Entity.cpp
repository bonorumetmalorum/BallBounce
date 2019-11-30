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
