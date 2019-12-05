#include "PhysicsSystem.h"



PhysicsSystem::PhysicsSystem(std::vector<Entity *> * world)
{
	physWorld = world;
	g = glm::vec3(0, -9.80665, 0);
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::update(float deltaTime, bool freeFall)
{
	for (Entity * e : *physWorld) {
		if (e->isKinematic()) {
			if (!freeFall) {
				std::cout << "applying forces" << std::endl;
				e->applyForce(g/e->getMass());
			}
			else {
				std::cout << "no forces applied, g = 9.81" << std::endl;
				e->setAcceleration(g);
			}
			e->updatePosition(deltaTime, freeFall);
		}
	}
}
