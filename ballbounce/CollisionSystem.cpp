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
		for (int j = 0; j < collisionWorld->size(); j++)
		{
			if (i == j)
				continue;
			if (collisionWorld->at(j)->isKinematic()) {
				glm::vec3 impulse = glm::vec3(0);
				glm::vec3 displacement = glm::vec3(0);
				if (collision(collisionWorld->at(i), collisionWorld->at(j), impulse, displacement)) {
					collisionWorld->at(j)->shiftPosition(displacement);
					collisionWorld->at(j)->updateVelocity(impulse);
				}
			}
		}
	}
}


bool CollisionSystem::collision(Entity * e1, Entity * e2, glm::vec3 & impulseOUT, glm::vec3 & displacementOUT)
{
	if (e1->getType() == 0) {
		Ball * b = reinterpret_cast<Ball *>(e2);
		Plane * p = reinterpret_cast<Plane *>(e1);
		float vertVel = b->getVelocity().y * (b->getCors() * -1.0f);
		impulseOUT = glm::vec3(0.0, vertVel, 0.0);
		return spherePlaneCollision(b, p, displacementOUT);
	}
	return false;
}

bool CollisionSystem::spherePlaneCollision(Ball * s, Plane * p, glm::vec3 & displacement)
{
	glm::vec3 directionToPlane = s->getPosition() - p->getPosition();
	float projection = glm::dot(p->getNormal(), directionToPlane);
	if (projection < s->getRadius()) {
		float magnitudeOfDisplacement = s->getRadius() - projection;
		glm::vec3 displacementDirection = p->getNormal();
		displacement = (displacementDirection * magnitudeOfDisplacement);
		return true;
	}
	return false;
}




