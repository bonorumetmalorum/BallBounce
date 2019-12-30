#pragma once
#include "Entity.h"
#include <vector>
#include "Ball.h"
#include "Plane.h"

class CollisionSystem
{
	struct CollisionEvent {
		Entity* e;
		glm::vec3 impulse;
	};

public:
	CollisionSystem(std::vector<Entity*> * collisionWorld);
	~CollisionSystem();
	void update();

private:
	std::vector<Entity*> * collisionWorld;
	void collision(Entity * e1, Entity * e2, std::vector<CollisionSystem::CollisionEvent> & eventOUT);
	bool spherePlaneCollision(Ball * spherCentre, Plane * p, glm::vec3 & displacement);
	bool sphereSphereCollision(Ball * a, Ball * b, glm::vec3 & displacement);
};

