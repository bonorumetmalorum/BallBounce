#include "RenderManager.h"



RenderManager::RenderManager()
{
	//init glfw
	if (!glfwInit())
		throw "error";

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Ball Bounce", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "error";
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//init glew openGL functions
	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;

	/*setup imgui*/
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsDark();
}

bool RenderManager::play() {
	return glfwWindowShouldClose(window);
}

void RenderManager::draw() {
	ball.draw();
	wall.draw();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();
}


RenderManager::~RenderManager()
{
}

void RenderManager::pollInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		playing = false;
	if (glfwGetKey(window, GLFW_KEY_W))
		//move camera forward in direction it is facing
		cam.moveForward(mvmtAmt);
	if (glfwGetKey(window, GLFW_KEY_S))
		//move camera backwards in direction it is facing
		cam.moveBack(mvmtAmt);
	if (glfwGetKey(window, GLFW_KEY_A))
		//move camera left
		cam.moveLeft(mvmtAmt);
	if(glfwGetKey(window, GLFW_KEY_D)
		//move camera right
		cam.moveRight(mvmtAmt);
}
