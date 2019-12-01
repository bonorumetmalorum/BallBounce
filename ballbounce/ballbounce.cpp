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
struct DeltaTime {
	float currentFrame = 0.0f;
	float lastFrame = 0.0f;
	float delta;
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

	DeltaTime dT;

	/* Loop until the user closes the window */
	while (!renderer.play())
	{
		//delta time calculations
		dT.currentFrame = glfwGetTime();
		dT.delta = dT.currentFrame - dT.lastFrame;
		dT.lastFrame = dT.currentFrame;

		//standard stuff
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		bool show = true;
		ImGui::ShowDemoWindow(&show);

			
		//renderer.draw(&b); //give the renderer an entity to draw, it will handle binding its VAO and Buffer data then calling gl draw
		//renderer.draw(&p);
		//p.update(dT.delta);
		//p.draw();

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
