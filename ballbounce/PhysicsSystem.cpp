#include "PhysicsSystem.h"



PhysicsSystem::PhysicsSystem(std::vector<Entity *> * world)
{
	physWorld = world;
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::update(float deltaTime)
{
	for (Entity * e : *physWorld) {
		if (e->isKinematic()) {
			e->applyForce(g);
			e->updatePosition(deltaTime);
		}
	}
}
