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


int createShaderProgram(const std::string & vs, const std::string & fs) {
	unsigned int prog = glCreateProgram();
	//shader types
	unsigned int v = glCreateShader(GL_VERTEX_SHADER);
	unsigned int f = glCreateShader(GL_FRAGMENT_SHADER);
	//compile source
	const char * vsrc = vs.c_str();
	const char * fsrc = fs.c_str();
	glShaderSource(v, 1, &vsrc, nullptr);
	glShaderSource(f, 1, &fsrc, nullptr);

	glCompileShader(v);
	glCompileShader(f);
	
	glAttachShader(prog, v);
	glAttachShader(prog, f);

	glLinkProgram(prog);
	glValidateProgram(prog);
	std::cout << glGetError() << std::endl;
	//clean up
	//glDeleteShader(v);
	//glDeleteShader(f);
	//use program
	//glUseProgram(prog);
	return prog;
}

void readShaders(std::string & vert, std::string & frag) {
	std::stringstream vertstream; 
	std::stringstream fragstream;
	std::ifstream vertShader;
	vertShader.open("./shaders/v_simple.shader");
	std::ifstream fragShader;
	fragShader.open("./shaders/f_simple.shader");
	vertstream << vertShader.rdbuf();
	fragstream << fragShader.rdbuf();
	vert = vertstream.str();
	frag = fragstream.str();
}

void create_triangle(unsigned int &vbo, unsigned int &vao, unsigned int &ebo)
{

	// create the triangle
	float triangle_vertices[] = {
		0.0f, 0.25f, 0.0f,	// position vertex 1
		1.0f, 0.0f, 0.0f,	 // color vertex 1
		0.25f, -0.25f, 0.0f,  // position vertex 1
		0.0f, 1.0f, 0.0f,	 // color vertex 1
		-0.25f, -0.25f, 0.0f, // position vertex 1
		0.0f, 0.0f, 1.0f,	 // color vertex 1
	};
	unsigned int triangle_indices[] = {
		0, 1, 2 };
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_indices), triangle_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


int main(void)
{
	GLFWwindow* window;
	
	//std::string vertexShader = "#version 330 core \n layout(location = 0) in vec3 aPos; // the position variable has attribute position 0 \n out vec4 vertexColor; // specify a color output to the fragment shader void\n main(){gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor\n	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color\n}";
	//std::string fragmentShader = "#version 330 core\n out vec4 FragColor; in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)\n void main(){FragColor = vertexColor;}";

	std::string vertexShader;
	std::string fragmentShader;
	readShaders(vertexShader, fragmentShader);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Ball Bounce", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;
	
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsDark();


	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	//Plane * p = new Plane();

	//float positions[6] = {
	//	-0.5f, -0.5f,
	//	0.0f, 0.0f,
	//	0.5f, 0.5f
	//};

	unsigned int vbo, vao, ebo;
	create_triangle(vbo, vao, ebo);
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//glGenBuffers(1, &buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	int prog = createShaderProgram(vertexShader, fragmentShader);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow(&show_demo_window);

		//p->draw();

		//render our geometries
		glUseProgram(prog);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
	
	return 0;
}
