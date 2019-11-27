#pragma once
#include "Ball.h"
#include "Plane.h"
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Camera.h"
class RenderManager
{
public:
	RenderManager();
	bool play();
	void draw();
	~RenderManager();

	void pollInput();

private:
	Ball ball;
	Plane wall;

	GLFWwindow * window;

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool playing = true;

	Camera cam;

	float deltaTime;
	float lastFrameTime;
};

