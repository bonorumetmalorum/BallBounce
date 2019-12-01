#include "CollisionSystem.h"



CollisionSystem::CollisionSystem(std::vector<Entity*> & collisionWorld)
{
	this->collisionWorld = collisionWorld;
}


CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::addEntity(Entity * e)
{
	collisionWorld.push_back(e);
}

void CollisionSystem::update() 
{
	for (int i = 0; i < collisionWorld.size(); i++) {
		if (collisionWorld[i]->isKinematic()) {
			//check if it collides
			//if it does updates its position so it no longer intersect
			//apply the impulse force to it
			//done, rinse and repeat
		}
	}
}

bool CollisionSystem::collision(int entityIndex, glm::vec3 & impulse, glm::vec3 & displacement)
{
	for (int i = 0; i < collisionWorld.size(); i++) {
		if (collisionWorld[i]->getType() == 1) {//ball

		}
		else if (collisionWorld[i]->getType() == 0) { // wall

		}
	}
}

bool CollisionSystem::sphereSphereCollision()
{
	return false;
}

bool CollisionSystem::spherePlaneCollision()
{
	return false;
}




