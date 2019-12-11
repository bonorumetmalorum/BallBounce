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

	void addBall(glm::vec3 position, float radius, float mass, float cors);

	void draw();
	void update(float deltaTime);
	void fixedUpdate();
	
	void play();
	void pause();
	void stop();

	void menu();

	float getTimeStep();

	bool getFixedUpdateEnabled();

	int getFrameRate();

	void reset();

	static void play_pause_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


private:
	static State state;
	std::vector<Entity*> world;
	PhysicsSystem * ps;
	CollisionSystem * cs;
	static RenderManager * rm;
	glm::vec3 tmpPos;
	float tmpScale = 1.0;
	float tmpMass;
	bool freeFall = false;
	float timeStep = 0.01;
	int frameRate = 60.0;
	float floorPosition;
	float tmpCors;
	glm::vec3 wind;
	bool fixedUpdateEnabled = false;
};

