#pragma once
#include "Entity.h"
#include <vector>
#include "Ball.h"
#include "Plane.h"

class CollisionSystem
{
public:
	CollisionSystem(std::vector<Entity*> * collisionWorld);
	~CollisionSystem();
	void update();

private:
	std::vector<Entity*> * collisionWorld;
	bool collision(Entity * e1, Entity * e2, glm::vec3 & impulseOUT, glm::vec3 & displacementOUT);
	bool spherePlaneCollision(Ball * spherCentre, Plane * p, glm::vec3 & displacement);
	bool sphereSphereCollision(Ball * a, Ball * b, glm::vec3 & displacement);
};