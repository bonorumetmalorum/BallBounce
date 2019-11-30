#pragma once
#include "Entity.h"
#include "tiny_obj_loader.h"
#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>

class Plane :
	public Entity
{
public:
	Plane();
	~Plane();

	void draw();
private:
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t wall;
	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;
	GLuint vao;
	glm::mat4x4 model;
};

