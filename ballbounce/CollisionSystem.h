#pragma once
#include "Entity.h"
#include <vector>
class CollisionSystem
{
public:
	CollisionSystem(std::vector<Entity*> & collisionWorld);
	~CollisionSystem();
	void addEntity(Entity * e);
	void update();

private:
	std::vector<Entity*> collisionWorld;
	bool collision(int entityIndex, glm::vec3 & impulse, glm::vec3 & displacement);
	bool sphereSphereCollision();
	bool spherePlaneCollision();
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
