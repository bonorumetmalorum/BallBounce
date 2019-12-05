// ballbounce.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Plane.h"
#include <fstream>
#include <sstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "RenderManager.h"
#include "PhysicsSystem.h"
#include "Simulator.h"

struct DeltaTime {
	float currentFrame = 0.0f;
	float lastFrame = 0.0f;
	float delta;
	float lag;
};

Camera camera;

void mouse_input_callback(GLFWwindow * window, double xoff, double yoff);

float prevX;
float prevY;

bool isStart;

int main(void)
{
	RenderManager renderer(&camera);

	//PhysicsSystem p(&renderer);


	//set call back function
	glfwSetCursorPosCallback(renderer.getWindow(), mouse_input_callback);

	//Ball b;
	//Plane p;

	Simulator * sim = new Simulator(&renderer);
	sim->addWall(glm::vec3(0.0, 0.0, 0.0), 200);
	sim->addBall(glm::vec3(5, 10.0, 0.0), 1, 1);
	sim->addBall(glm::vec3(0.0, 10.0, 0.0), 1, 1);

	DeltaTime dT;
	dT.lag = 0.0;

	/* Loop until the user closes the window */
	while (!renderer.play())
	{
		//delta time calculations
		dT.currentFrame = glfwGetTime();
		dT.delta = dT.currentFrame - dT.lastFrame;
		dT.lag += dT.delta;
		dT.lastFrame = dT.currentFrame;

		//standard stuff
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		while (dT.lag >= sim->getTimeStep()) {
			sim->fixedUpdate();
			dT.lag -= sim->getTimeStep();
		}

		sim->draw();
		
		glfwSwapBuffers(renderer.getWindow());

		renderer.pollInput(dT.delta);
	}

	return 0; 
}
//TODO
static void mouse_input_callback(GLFWwindow * window, double xoff, double yoff)
{
	if (isStart) {
		prevX = xoff; //maybe refactor this out of global scope
		prevY = yoff; //this too
		isStart = false;
	}

	float x = xoff - prevX;
	float y = prevY - yoff;

	prevX = xoff;
	prevY = yoff;

	camera.look(x, y);
}
