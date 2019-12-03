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
	bool collision(int entityIndex, Entity * e, glm::vec3 & impulseOUT, glm::vec3 & displacementOUT);
	bool sphereSphereCollision(glm::vec3 spherCentre, float radius, glm::vec3 sphereCentreOther, float radiusOther, glm::vec3 & displacement);
	bool spherePlaneCollision(Ball * spherCentre, Plane * p, glm::vec3 & displacement);
};

/**
	The collision system will maintain a collision world
	The collision world will keep track of collidable entities
	the collision system must
		have a method to check for collisions
			this method will return an index of the colliding entities and 
			the distance by which to move them such they are no longer intersecting/colliding
		have private methods to handle collisions between spheres (balls) and spheres and spheres and planes/points (walls)
*/
