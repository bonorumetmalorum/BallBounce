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
	Ball(glm::vec3 position, float scale, float mass, float cors);
	~Ball();

	void applyForce(glm::vec3 force);

	void updatePosition(float deltatTime, bool freeFall) override;
	
	void draw();

	float getRadius();

	float getCors();

	glm::vec3 getVelocity();

private:
	void loadMesh();
	float radius;
	
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t ball;
	
	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint indexBuffer;
	GLuint vao;
	
	float mass = 1.0;
	float cors = 0.0;


};

