#pragma once
#include "Entity.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "glm.hpp"

#include <vector>
#include <memory>

enum State {
	PLAY,
	PAUSE,
	STEP,
	SETUP,
	STOP
};

class Simulator
{
public:
	Simulator(RenderManager * r);
	~Simulator();



	void addBall(glm::vec3 position, float scale);
	void addWall(glm::vec3 position, float angle);

	void draw();
	void update(float deltaTime);
	void play();
	void pause();
	void step();
	void stop();

	void menu();

	void setup();

private:
	State state = State::SETUP;
	std::vector<Entity*> world;
	PhysicsSystem * ps;
	CollisionSystem * cs;
	RenderManager * rm;
	glm::vec3 tmpPos;
	float tmpScale;

};

/**
	the simulator class must:
		keep track of the number of entities in the scene
		allow to add more entities
		allow to step through the simulation, one step at a time
		indefinitely loop through the simulation until exit

*/

