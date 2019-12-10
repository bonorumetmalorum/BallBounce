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
					//collisionWorld->at(j)->updateVelocity(impulse);
				}
			}
		}
	}
}


bool CollisionSystem::collision(Entity * e1, Entity * e2, glm::vec3 & impulseOUT, glm::vec3 & displacementOUT)
{
	if (e1->getType() == 1) {
		
		Ball * a = reinterpret_cast<Ball *>(e2);
		Ball * b = reinterpret_cast<Ball *>(e1);

		if (sphereSphereCollision(a, b, displacementOUT)) {

			glm::vec3 veca = a->getPosition() - b->getPosition();
			veca = glm::normalize(veca);

			glm::vec3 avel = a->getVelocity();
			float axdot = glm::dot(glm::vec3(1, 0, 0), avel);
			glm::vec3 avecx = veca * axdot;
			glm::vec3 avecy = avel - avecx;

			glm::vec3 vecb = b->getPosition() - a->getPosition();
			vecb = glm::normalize(vecb);
			glm::vec3 bvel = b->getVelocity( );
			float bxdot = glm::dot(glm::vec3(1, 0, 0), bvel);
			glm::vec3 bvecx = vecb * bxdot;
			glm::vec3 bvecy = bvel - bvecx;

			glm::vec3 impulsea = 
				avecx * (a->getMass() * b->getMass()) / (a->getMass() + b->getMass()) + 
				bvecx * (2 * b->getMass()) / (a->getMass() + b->getMass()) + avecy;
			glm::vec3 impulseb = 
				avecx * (2 * a->getMass()) / (a->getMass() + b->getMass()) + 
				bvecx * (b->getMass() - a->getMass()) / (a->getMass() + b->getMass()) + bvecy;

			//a->shiftPosition(a->getPosition() - 1.0f);
			//b->shiftPosition(b->getPosition() - 1.0f);

			a->updateVelocity(impulsea);
			b->updateVelocity(impulseb);
			return true;
		}
		else {
			return false;
		}
	}
	if (e1->getType() == 0) {
		Ball * b = reinterpret_cast<Ball *>(e2);
		Plane * p = reinterpret_cast<Plane *>(e1);
		float vertVel = b->getVelocity().y * (b->getCors() * -1.0f);
		if (spherePlaneCollision(b, p, displacementOUT)) {
			glm::vec3 impulse = glm::vec3(0.0, vertVel, 0.0);
			b->updateVelocity(impulse);
			return true;
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

bool CollisionSystem::sphereSphereCollision(Ball * a, Ball * b, glm::vec3 & displacement)
{
	glm::vec3 c1ToC2 = a->getPosition() - b->getPosition();
	float radiusSum = a->getRadius() + b->getRadius();
	float distanceBetweenCentres = glm::length(c1ToC2);
	if (distanceBetweenCentres < radiusSum) {
		float magnitudeOfDisplacement = radiusSum - distanceBetweenCentres;
		glm::vec3 displacementDirection = glm::normalize(c1ToC2);
		displacement = displacementDirection * magnitudeOfDisplacement;
		b->shiftPosition(displacement);
		std::cout << "sphere collision" << std::endl;
		return true;
	}
	return false;
}




