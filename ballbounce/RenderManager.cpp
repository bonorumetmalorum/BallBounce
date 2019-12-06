#include "RenderManager.h"



bool RenderManager::isInMenuMode = false;

Camera * RenderManager::cam;

GLFWwindow * RenderManager::window;


RenderManager::RenderManager(Camera * camera)
{
	isInMenuMode = false;

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

	//glfwSetCursorPosCallback(window, &cam.look);

	std::string vert, frag;
	readShaders(vert, frag);
	createShaderProgram(vert, frag);

	cam = camera;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(window, key_callback);
}

void RenderManager::drawMenus(GLFWwindow * window) {

}

bool RenderManager::play() {
	return glfwWindowShouldClose(window);
}

void RenderManager::draw(Entity * e) {


	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	//replace this with camera stuff----

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, e->getPosition());
	model = glm::scale(model, glm::vec3(e->getScale()));
	
	glm::mat4 view = glm::lookAt(cam->getPosition(), cam->getPosition() + cam->getFront(), cam->getUp());

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), float(display_w) / float(display_h), 0.1f, 1000.0f);
	//-----
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

	glUseProgram(shaderProgram);
	//draw entity

	glUniform1i(glGetUniformLocation(shaderProgram, "type"), e->getType());

	e->draw();
}


RenderManager::~RenderManager()
{
}

void RenderManager::pollInput(float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		playing = false;
		glfwSetWindowShouldClose(window, true);
	}
		
	if (glfwGetKey(window, GLFW_KEY_W))
		//move camera forward in direction it is facing
		cam->moveForward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		//move camera backwards in direction it is facing
		cam->moveBack(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		//move camera left
		cam->moveLeft(deltaTime);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		//move camera right
		cam->moveRight(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam->moveUp(deltaTime);
}

GLFWwindow* RenderManager::getWindow()
{
	return window;
}

void RenderManager::switchInputMode()
{
	if (isInMenuMode) {
		isInMenuMode = false;
		//std::cout << "quitting menu mode" << std::endl;
		cam->freeze();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		isInMenuMode = true;
		//std::cout << "entering menu mode" << std::endl;
		cam->freeze();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void RenderManager::readShaders(std::string & vert, std::string & frag) {
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

void RenderManager::createShaderProgram(const std::string & vs, const std::string & fs) {
	shaderProgram = glCreateProgram();
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

	glAttachShader(shaderProgram, v);
	glAttachShader(shaderProgram, f);

	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);
	std::cout << glGetError() << std::endl;
	//clean up
	//glDeleteShader(v);
	//glDeleteShader(f);
	//use program
	//glUseProgram(prog);
}

void RenderManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		switchInputMode();
	}
}
