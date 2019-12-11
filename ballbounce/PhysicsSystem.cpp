#include "PhysicsSystem.h"



PhysicsSystem::PhysicsSystem(std::vector<Entity *> * world)
{
	physWorld = world;
	g = glm::vec3(0, -9.80665, 0);

}


PhysicsSystem::~PhysicsSystem()
{
}

/*
	applies all forces to entities and updates their positions accordingly
	@param deltaTime the change in time
	@param freeFall true to apply force false to have acceleration = 9.81 m/s^2
*/
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

/*
	sets the wind force in the scene
	@param wind a vector defining the force of wind in each axis
*/
void PhysicsSystem::setWind(glm::vec3 wind)
{
	this->wind = wind;
}
