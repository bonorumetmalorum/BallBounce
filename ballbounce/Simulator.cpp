#include "Simulator.h"



Simulator::Simulator(RenderManager * r)
{
	ps = new PhysicsSystem(world);
	cs = new CollisionSystem(world);
	rm = r;
}


Simulator::~Simulator()
{
}

void Simulator::addBall(glm::vec3 position)
{
	world.push_back(new Ball(position));
}

void Simulator::addWall(glm::vec3 position, float angle)
{
	world.push_back(new Plane(position));
}

void Simulator::draw()
{
	for (Entity * e : world) {
		e->draw();
	}
}

void Simulator::update(float deltaTime)
{
	cs->update();
	ps->update(deltaTime);

}
