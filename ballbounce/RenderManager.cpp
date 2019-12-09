#include "RenderManager.h"



bool RenderManager::isInMenuMode = false;

Camera * RenderManager::cam;

GLFWwindow * RenderManager::window;

double RenderManager::lastxpos;
double RenderManager::lastypos;


RenderManager::RenderManager(Camera * camera)
{
	isInMenuMode = false;

	if (!glfwInit())
		throw "error";

	window = glfwCreateWindow(1280, 720, "Ball Bounce", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "error";
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsDark();

	std::string vert, frag;
	readShaders(vert, frag);
	createShaderProgram(vert, frag);

	cam = camera;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(window, key_callback);
}

bool RenderManager::play() {
	return glfwWindowShouldClose(window);
}

void RenderManager::draw(Entity * e) {


	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, e->getPosition());
	model = glm::scale(model, glm::vec3(e->getScale()));
	
	glm::mat4 view = glm::lookAt(cam->getPosition(), cam->getPosition() + cam->getFront(), cam->getUp());

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(cam->getFov()), float(display_w) / float(display_h), 0.1f, 1000.0f);
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

	glUseProgram(shaderProgram);

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
		cam->moveForward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam->moveBack(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam->moveLeft(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam->moveRight(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam->moveUp(deltaTime);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	this->cam->look(mouseX, mouseY);
}

GLFWwindow* RenderManager::getWindow()
{
	return window;
}

void RenderManager::switchInputMode()
{
	if (isInMenuMode) {
		isInMenuMode = false;
		cam->freeze();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(window, lastxpos, lastypos);
	}
	else {
		isInMenuMode = true;
		glfwGetCursorPos(window, &lastxpos, &lastypos);
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

	unsigned int v = glCreateShader(GL_VERTEX_SHADER);
	unsigned int f = glCreateShader(GL_FRAGMENT_SHADER);

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
}

void RenderManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		switchInputMode();
	}
}
