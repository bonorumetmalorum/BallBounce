#include "Ball.h"
#include <iostream>


Ball::Ball(glm::vec3 position, float radius, float mass, float cors) : Entity(position, radius, mass, 1)
{
	loadMesh();
	this->radius = radius;
	kinematic = true;
	this->cors = cors;
	force = glm::vec3(0.0, mass * 9.81f, 0.0);
}

Ball::~Ball()
{
}

void Ball::applyForce(glm::vec3 force)
{
	this->force += force;
}

void Ball::updatePosition(float deltaTime, bool freeFall)
{
	if (!freeFall) {
		acceleration = force / mass;
	}
	velocity += (acceleration * deltaTime);
	position += velocity;
	acceleration = glm::vec3(0);
	force = glm::vec3(0);
}

void Ball::draw()
{
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, 3 * shapes[0].mesh.num_face_vertices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

float Ball::getRadius()
{
	return radius;
}

float Ball::getCors()
{
	return cors;
}

glm::vec3 Ball::getVelocity()
{
	return velocity;
}

void Ball::loadMesh() {
	std::string warn;
	std::string err;
	if (!tinyobj::LoadObj(&this->ball, &this->shapes, &this->materials, &warn, &err, "./assets/ball/ball.obj", "./assets/ball/")) {
		std::cout << "warning: " << warn << "\n" << "errors: " << err << std::endl;
	}

	if (!ball.vertices.empty()) {
		glGenBuffers(1, &this->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, ball.vertices.size() * sizeof(float), this->ball.vertices.data(), GL_STATIC_DRAW);
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

	if (indexBuffer != 0) {
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
		glBindVertexArray(0);
	}
}

