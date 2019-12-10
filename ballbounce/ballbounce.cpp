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
#include <thread>

struct DeltaTime {
	float currentFrame = 0.0f;
	float lastFrame = 0.0f;
	float delta;
	float lag;
	float timeAcc;
};

Camera camera;

void scroll_input_callback(GLFWwindow * window, double xoff, double yoff);

int main(void)
{
	RenderManager renderer(&camera);

	glfwSetScrollCallback(renderer.getWindow(), scroll_input_callback);

	Simulator * sim = new Simulator(&renderer);
	sim->addBall(glm::vec3(1.0, 13.0, 0.0), 1, 1, 1);
	sim->addBall(glm::vec3(0.0, 10.0, 0.0), 1, 1, 1);

	DeltaTime dT;
	dT.lag = 0.0;
	dT.lastFrame = 0.0;
	dT.timeAcc = 0;
	float FPS;

	while (!renderer.play())
	{
		//delta time calculations
		dT.currentFrame = glfwGetTime();
		dT.delta = dT.currentFrame - dT.lastFrame;
		dT.lag += dT.delta;
		dT.timeAcc += dT.delta;
		dT.lastFrame = dT.currentFrame;
		
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);

		if (sim->getFixedUpdateEnabled()) {
			while (dT.lag >= sim->getTimeStep()) {
				sim->fixedUpdate();
				dT.lag -= sim->getTimeStep();
			}
		}
		else {
			sim->update(dT.delta);
		}

		if (dT.timeAcc < (1 / (float)sim->getFrameRate())) {
		}
		else {
			sim->draw();
			dT.timeAcc = 0;
		}
		
		renderer.pollInput(dT.delta);
	}

	return 0; 
}


static void scroll_input_callback(GLFWwindow * window, double xoff, double yoff) {
	camera.updateFov(yoff);
}