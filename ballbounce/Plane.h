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
	Plane(glm::vec3 position, float scale);
	~Plane();

	void draw();

	glm::vec3 getNormal();

	glm::vec3 getVertex(int index);

private:

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t wall;
	
	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;
	GLuint vao;
	
	glm::vec3 normal = glm::vec3(0.0,1.0,0.0);

	void loadMesh();
};

