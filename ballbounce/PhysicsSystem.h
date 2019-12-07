#pragma once

#include "CollisionSystem.h"
#include "Ball.h"
#include "Plane.h"
#include "RenderManager.h"
#include <memory>

class PhysicsSystem
{
public:
	PhysicsSystem(std::vector<Entity *> *world);
	~PhysicsSystem();

	void update(float deltaTime, bool freeFall);

	void setWind(glm::vec3 wind);

private:
	std::vector<Entity *> * physWorld;
	glm::vec3 g = glm::vec3(0, -9.80665, 0);
	glm::vec3 wind = glm::vec3(0);
};

/**
	must maintain a physics world
	the physics world will keep track of entities that will have forces acted upon them
	this system will be closely coupled to the collision system


*/