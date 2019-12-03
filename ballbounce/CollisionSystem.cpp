#include "CollisionSystem.h"
#include "gtx/transform.hpp"


CollisionSystem::CollisionSystem(std::vector<Entity*> * collisionWorld)
{
	this->collisionWorld = collisionWorld;
}


CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::update() 
{
	for (int i = 0; i < collisionWorld->size(); i++) {
		if (collisionWorld->at(i)->isKinematic()) {
			glm::vec3 impulse = glm::vec3(0);
			glm::vec3 displacement = glm::vec3(0);
			if (collision(i, collisionWorld->at(i), impulse, displacement)) {
				collisionWorld->at(i)->shiftPosition(displacement);
				collisionWorld->at(i)->applyForce(impulse);
			}
			else {
				continue;
			}
		}
	}
}

//maybe return an array of collision items, these items will then need to be resolved in the calling method
//this is good for now TODO
bool CollisionSystem::collision(int entityIndex, Entity * e, glm::vec3 & impulseOUT, glm::vec3 & displacementOUT)
{
	for (int i = 0; i < collisionWorld->size(); i++) {
		if (i == entityIndex) {
			continue;
		}
		if (collisionWorld->at(i)->getType() == 1) {//ball
			Ball * b = static_cast<Ball *>(e);
			Ball * bOther = static_cast<Ball *>(collisionWorld->at(i));
			return sphereSphereCollision(b->getPosition(), b->getRadius(), bOther->getPosition(), bOther->getRadius(), displacementOUT);
		}
		else if (collisionWorld->at(i)->getType() == 0) { // wall
			Ball * b = static_cast<Ball *>(e);
			Plane * p = static_cast<Plane *>(collisionWorld->at(i));
			return spherePlaneCollision(b, p, displacementOUT);
		}
	}
	return false;
}

bool CollisionSystem::sphereSphereCollision(glm::vec3 spherCentre, float radius, glm::vec3 sphereCentreOther, float radiusOther, glm::vec3 & displacement)
{
	glm::vec3 c1ToC2 = sphereCentreOther - sphereCentreOther;
	float radiusSum = radius + radiusOther;
	float distanceBetweenCentres = glm::length(c1ToC2);
	if ( distanceBetweenCentres < radiusSum) {
		float magnitudeOfDisplacement = radius - distanceBetweenCentres;
		glm::vec3 displacementDirection = glm::normalize(c1ToC2);
		displacement = displacementDirection * magnitudeOfDisplacement;
		return true;
	}
	return false;
}

bool CollisionSystem::spherePlaneCollision(Ball * s, Plane * p, glm::vec3 & displacement)
{
	glm::vec3 directionToPlane = p->getPosition() - s->getPosition();
	float distanceFromPlane = glm::length(directionToPlane);
	if (distanceFromPlane < s->getRadius()) {
		float magnitudeOfDisplacement = s->getRadius() - distanceFromPlane;
		glm::vec3 displacementDirection = p->getNormal();
		displacement = displacementDirection * magnitudeOfDisplacement;
		return true;
	}
	return false;
}




