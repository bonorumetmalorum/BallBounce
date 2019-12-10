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
				e->applyForce(g*e->getMass());
				e->applyForce(wind);
			}
			else {
				e->setAcceleration(g);
			}
			e->updatePosition(deltaTime, freeFall);
		}
	}
}

void PhysicsSystem::setWind(glm::vec3 wind)
{
	this->wind = wind;
}
