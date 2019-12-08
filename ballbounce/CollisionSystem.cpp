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
				collisionWorld->at(i)->updateVelocity(impulse);
			}
		}
	}
}


bool CollisionSystem::collision(int entityIndex, Entity * e, glm::vec3 & impulseOUT, glm::vec3 & displacementOUT)
{
	//TODO
	for (int i = 0; i < collisionWorld->size(); i++) {
		if (i == entityIndex) {
			continue;
		}
		if (collisionWorld->at(i)->getType() == 0) {
			Ball * b = reinterpret_cast<Ball *>(e);
			Plane * p = reinterpret_cast<Plane *>(collisionWorld->at(0));
			float vertVel = b->getVelocity().y * (b->getCors() * -1.0f);
			impulseOUT = glm::vec3(0.0, vertVel, 0.0);
			std::cout << impulseOUT.x << " " << impulseOUT.y << " " << impulseOUT.z << std::endl;
			return spherePlaneCollision(b, p, displacementOUT);
		}
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




