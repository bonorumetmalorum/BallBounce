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
	Ball();
	~Ball();

	void draw();

private:
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

};

