#pragma once
class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
};

/**
	must maintain a physics world
	the physics world will keep track of entities that will have forces acted upon them
	this system will be closely coupled to the collision system


*/