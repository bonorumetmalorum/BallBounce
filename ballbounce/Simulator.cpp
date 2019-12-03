#include "Simulator.h"



Simulator::Simulator(RenderManager * r)
{
	ps = new PhysicsSystem(&world);
	cs = new CollisionSystem(&world);
	rm = r;
}


Simulator::~Simulator()
{
}

void Simulator::addBall(glm::vec3 position, float scale)
{
	world.push_back(new Ball(position, scale));
}

void Simulator::addWall(glm::vec3 position, float scale)
{
	world.push_back(new Plane(position, scale));
}

void Simulator::draw()
{
	for (Entity * e : world) {
		this->rm->draw(e);
	}
}

void Simulator::update(float deltaTime)
{
	//cs->update();
	ps->update(deltaTime);

}
