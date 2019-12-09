#include "Plane.h"



Plane::Plane(glm::vec3 position, float scale) : Entity(position, scale, 0.0, 0)
{
	loadMesh();
}

void Plane::loadMesh() 
{
	std::string warn;
	std::string err;
	if (!tinyobj::LoadObj(&this->wall, &this->shapes, &this->materials, &warn, &err, "./assets/wall/wall.obj", "./assets/wall/")) {
		std::cout << "warning: " << warn << "\n" << "errors: " << err << std::endl;
	}

	if (!wall.vertices.empty()) {
		glGenBuffers(1, &this->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, wall.vertices.size() * sizeof(float), this->wall.vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (!wall.texcoords.empty()) {
		glGenBuffers(1, &this->textureBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->textureBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->wall.texcoords.size() * sizeof(float), this->wall.texcoords.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (!shapes[0].mesh.indices.empty()) {
		std::vector<int> indices;
		for (auto & shape : shapes[0].mesh.indices) {
			indices.push_back(shape.vertex_index);
		}
		glGenBuffers(1, &this->indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->shapes[0].mesh.indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	glGenVertexArrays(1, &this->vao);

	if (vertexBuffer != 0) {
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	if (textureBuffer != 0) {
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->textureBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);
	}

	if (indexBuffer != 0) {
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
		glBindVertexArray(0);
	}
}


Plane::~Plane()
{
}




void Plane::draw()
{
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, shapes[0].mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

glm::vec3 Plane::getNormal()
{
	return normal;
}

glm::vec3 Plane::getVertex(int index)
{
	glm::vec3 vertex;
	vertex.x = wall.vertices[index];
	vertex.x = wall.vertices[index+1];
	vertex.x = wall.vertices[index+2];
	return vertex;
}

