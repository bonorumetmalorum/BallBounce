#pragma once
#include "Entity.h"
#include "tiny_obj_loader.h"
#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>

class Ball :
	public Entity
{
public:
	Ball(glm::vec3 position, float scale, float mass, float cors, glm::vec3 vel);
	~Ball();

	void applyForce(glm::vec3 force);

	void updatePosition(float deltatTime, bool freeFall) override;
	
	void draw();

	float getRadius();

	float getCors();

	void reset() override;

private:
	void loadMesh();
	float radius;
	glm::vec3 initVelocity = glm::vec3(0.0f);
	
	static std::vector<tinyobj::shape_t> shapes;
	static std::vector<tinyobj::material_t> materials;
	static tinyobj::attrib_t ball;
	
	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint vao;
	
	float mass = 1.0;
	float cors = 0.0;


};

