#pragma once

#include "CollisionSystem.h"
#include "Ball.h"
#include "Plane.h"
#include "RenderManager.h"

class PhysicsSystem
{
public:
	PhysicsSystem(RenderManager * r);
	~PhysicsSystem();

	//void pause();

	void update(float deltaTime);

	void draw();

	//void step();

	GLFWwindow * getWindow();
	

private:

	const glm::vec3 g = glm::vec3(0, -0.0000980665, 0);

	Ball * b;

	Plane * w;

	CollisionSystem * collisionWorld;

	RenderManager * renderer;	
};

/**
	must maintain a physics world
	the physics world will keep track of entities that will have forces acted upon them
	this system will be closely coupled to the collision system


*/