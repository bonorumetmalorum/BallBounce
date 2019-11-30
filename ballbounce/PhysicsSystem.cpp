#include "PhysicsSystem.h"



PhysicsSystem::PhysicsSystem(RenderManager * r)
{
	renderer = r;
	b = new Ball();
	w = new Plane();
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::update(float deltaTime)
{
	b->applyForce(g);
	b->updatePosition(deltaTime);
}

void PhysicsSystem::draw()
{
	renderer->draw(b);
	renderer->draw(w);
}

GLFWwindow * PhysicsSystem::getWindow()
{
	return renderer->getWindow();
}
