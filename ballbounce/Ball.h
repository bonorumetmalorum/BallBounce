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
	Ball(glm::vec3 position, float scale, float mass);
	~Ball();

	void applyForce(glm::vec3 force);

	void updatePosition(float deltatTime);

	void draw();

	float getRadius();

private:
	void loadMesh();
	float radius;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t ball;
	std::string path = "./assets/ball.obj";
	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;
	GLuint vao;
	glm::mat4x4 model;

	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	float mass = 1.0;


};

