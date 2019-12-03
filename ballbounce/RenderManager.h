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
#include <fstream>
#include <sstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class RenderManager
{
public:
	RenderManager(Camera * c);
	bool play();
	void draw(Entity * e);
	~RenderManager();

	void pollInput(float deltaTime);

	GLFWwindow* getWindow();

private:
	//Ball ball;
	//Plane wall;

	GLFWwindow * window;
	static bool isInMenuMode;
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool playing = true;

	int shaderProgram;

	static Camera * cam;

	float lastFrameTime;
	void readShaders(std::string & vert, std::string & frag);

	void createShaderProgram(const std::string & vs, const std::string & fs);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

