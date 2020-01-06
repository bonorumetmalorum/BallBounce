#include "CollisionSystem.h"
#include "gtx/transform.hpp"

/*
	creates a new collision system entity
*/
CollisionSystem::CollisionSystem(std::vector<Entity*> * collisionWorld)
{
	this->collisionWorld = collisionWorld;
}

CollisionSystem::~CollisionSystem()
{

}

/*
	updates the colliding entities, changing their velocities and shifting them such that they are no longer intersecting
*/
void CollisionSystem::update() 
{
	std::vector<CollisionEvent> sphereEvents;
	std::vector<CollisionEvent> planeEvents;
	for (int i = 0; i < collisionWorld->size(); i++) {
		for (int j = 0; j < collisionWorld->size(); j++)
		{
			if (i == j)
				continue;
			collision(collisionWorld->at(i), collisionWorld->at(j), sphereEvents, planeEvents);
		}
	}
	for (CollisionEvent ev : sphereEvents) {
		ev.e->updateVelocity(ev.impulse);
	}
	for (CollisionEvent ev : planeEvents) {
		ev.e->updateVelocity(ev.impulse);
	}
}

void CollisionSystem::collision(Entity * e1, Entity * e2, std::vector<CollisionSystem::CollisionEvent> & sphereEventOUT, std::vector<CollisionSystem::CollisionEvent>& planeEventOUT)
{
	glm::vec3 impulse;
	glm::vec3 shift;
	if (e1->getType() == 1 && e2->getType() == 1) {
		
		Ball * a = reinterpret_cast<Ball *>(e1);
		Ball * b = reinterpret_cast<Ball *>(e2);

		if (sphereSphereCollision(a, b, shift)) {

			e1->shiftPosition(shift/2.0f);
			e2->shiftPosition(shift / 2.0f * -1.0f);

			glm::vec3 speeda = (a->getMass() * a->getVelocity() + b->getMass()*b->getVelocity() + b->getMass() * (a->getCors() * (b->getVelocity() - a->getVelocity()))) / (a->getMass() + b->getMass());
			glm::vec3 speedb = (a->getMass() * a->getVelocity() + b->getMass()*b->getVelocity() + a->getMass() * (a->getCors() * (a->getVelocity() - b->getVelocity()))) / (a->getMass() + b->getMass());

			CollisionEvent ev1{e1, speedb };
			CollisionEvent ev2{e2, speeda };
			sphereEventOUT.push_back(ev1);
				sphereEventOUT.push_back(ev2);
			return;
		}
		else {
			return;
		}
	}
	if (e1->getType() == 0 || e2->getType() == 0) {
		Ball* b;

		if (e1->getType() == 1)
			b = reinterpret_cast<Ball*>(e1);
		else
			b = reinterpret_cast<Ball*>(e2);

		Plane* p;

		if (e1->getType() == 0)
			p = reinterpret_cast<Plane*>(e1);
		else
			p = reinterpret_cast<Plane*>(e2);
		float vertVel = b->getVelocity().y * (b->getCors() * -1.0f);
		if (spherePlaneCollision(b, p, shift)) {
			b->shiftPosition(shift);
			glm::vec3 impulse = glm::vec3(0.0, vertVel, 0.0);
			CollisionEvent ev{ e2, impulse };
			planeEventOUT.push_back(ev);
			return;
		}
	}
}

bool CollisionSystem::spherePlaneCollision(Ball * s, Plane * p, glm::vec3 & displacement)
{
	if (s->getPosition().y <= p->getPosition().y) {
		std::cout << "below plane adjusting y position" << std::endl;
		glm::vec3 newpos = (s->getPosition() + glm::vec3(0, p->getPosition().y + s->getRadius(), 0));
		s->setPosition(newpos);
	}
	glm::vec3 directionToPlane = s->getPosition() - p->getPosition();
	float projection = glm::dot(p->getNormal(), directionToPlane);
	if (projection < s->getRadius()) {
		//std::cout << "sphere plane collision" << std::endl;
		float magnitudeOfDisplacement = s->getRadius() - projection;
		glm::vec3 displacementDirection = p->getNormal();
		displacement = (displacementDirection * magnitudeOfDisplacement);
		return true;
	}
	return false;
}

bool CollisionSystem::sphereSphereCollision(Ball * a, Ball * b, glm::vec3 & displacement)
{
	glm::vec3 c1ToC2 = a->getPosition() - b->getPosition();
	if (c1ToC2 == glm::vec3(0.0f)) {
		std::cout << "completely overlapping" << std::endl;
		displacement = glm::vec3(0.0f, a->getRadius(), 0.0f);
		return true;
	}
	float radiusSum = a->getRadius() + b->getRadius();
	float distanceBetweenCentres = glm::length(c1ToC2);
	if (distanceBetweenCentres < radiusSum) {
		float magnitudeOfDisplacement = radiusSum - distanceBetweenCentres;
		glm::vec3 displacementDirection = glm::normalize(c1ToC2);
		displacement = displacementDirection * magnitudeOfDisplacement;
		//std::cout << "sphere collision" << std::endl;
		return true;
	}
	return false;
}




