#include "Simulator.h"


/*
	static instances to work with GLFW
*/
RenderManager * Simulator::rm;
State Simulator::state = State::SETUP;

/*
	returns a new instance of the simulator, the access point to the physical simulation
	@return Simulator instance
*/
Simulator::Simulator(RenderManager * r)
{
	ps = new PhysicsSystem(&world);
	cs = new CollisionSystem(&world);
	rm = r;
	state = State::SETUP;
	rm->switchInputMode();
	world.push_back(new Plane(glm::vec3(0), 200));
	glfwSetKeyCallback(rm->getWindow(), play_pause_input_callback);
}

/*
	a convenience binding for GLFW to support keyboard play pause functionality
*/
void Simulator::play_pause_input_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS) {
		if (state == PLAY) {
			state = PAUSE;
		}
		else {
			state = PLAY;
		}
		std::cout << "hello" << std::endl;
	}
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		rm->switchInputMode();
	}
}


Simulator::~Simulator()
{
}

/*
	adds a new ball to the simulation
	@param position the position of the ball
	@param radius the radius of the ball
	@param mass the mass of the ball
	@param cors the coefficient of restitution (bounciness)
*/
void Simulator::addBall(glm::vec3 position, float radius, float mass, float cors, glm::vec3 vel = glm::vec3(0.0f))
{
	world.push_back(new Ball(position, radius, mass, cors, vel));
}

/*
	draws all the entities in the simulation using the current instance of the RenderManager instantiated for this simulator
*/
void Simulator::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int display_w, display_h;
	glfwGetFramebufferSize(rm->getWindow(), &display_w, &display_h);
	menu();
	for (Entity * e : world) {
		this->rm->draw(e);
	}
	
	ImGui::Render();

	glViewport(0, 0, display_w, display_h);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(rm->getWindow());
}

/*
	updates all the entities in the simulation using collision detection and physics, in freefall or taking into account other forces
	@param deltaTime the change in time
*/
void Simulator::update(float deltaTime)
{
	world.at(0)->setPosition(glm::vec3(0, floorPosition, 0));
	ps->setWind(wind);
	if (state == State::PLAY) {
		cs->update();
		ps->update(deltaTime, freeFall);
	}
}

/*
	updates all the entities in the simulation using collision detection and physics, freefall or taking into account other forces
	However, this updates in fixed time steps
*/
void Simulator::fixedUpdate()
{
	world.at(0)->setPosition(glm::vec3(0, floorPosition, 0));
	ps->setWind(wind);
	if (state == State::PLAY) {
		cs->update();
		ps->update(this->timeStep, freeFall);
	}
}

/*
	sets the state of the simulation to PLAY (runs the simulation)
*/
void Simulator::play()
{
	state = State::PLAY;
}

/*
	sets the state of the simulation to PAUSE and stops advancing the simulation
*/
void Simulator::pause()
{
	state = State::PAUSE;
}

/*
	sets the state of the simulation to STOP and resets the positions of all entities to their starting position
*/
void Simulator::stop()
{
	state = State::STOP;
	for (Entity * e : world) {
		e->reset();
	}
}

/*
	removes all entities except the floor
*/
void Simulator::reset() {
	world.clear();
	world.push_back(new Plane(glm::vec3(0), 200));
}

/*
	function that contains the menu items for the simulation
*/
void Simulator::menu()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	ImGui::Begin("Menu");

	ImGui::Text("Add Ball");
	ImGui::InputFloat("x position", &tmpPos.x);
	ImGui::InputFloat("y position", &tmpPos.y);
	ImGui::InputFloat("z position", &tmpPos.z);
	ImGui::InputFloat("mass", &tmpMass);
	ImGui::SliderFloat("radius", &tmpScale, 1.0f, 10.0f);
	ImGui::SliderFloat("coefficient of restitution", &tmpCors, 0.0f, 1.0f);
	ImGui::InputFloat("x velocity", &tmpVel.x);
	ImGui::InputFloat("y velocity", &tmpVel.y);
	ImGui::InputFloat("z velocity", &tmpVel.z);


	if (ImGui::Button("Add")) {
		addBall(tmpPos, tmpScale, tmpMass, tmpCors, tmpVel);
	}

	ImGui::Text("Physics mode");
	ImGui::Checkbox("free fall", &freeFall);

	ImGui::Text("Floor Position");
	ImGui::InputFloat("floor height", &floorPosition);

	ImGui::Text("Sim Controls");
	if (ImGui::Button("Play")) {
		play();
	}
	if (ImGui::Button("Pause")) {
		pause();
	}
	if (ImGui::Button("Stop")) {
		stop();
	}
	if (ImGui::Button("Reset")) {
		reset();
	}
	ImGui::End();

	ImGui::Begin("Fixed Update");
	ImGui::SliderFloat("number of steps per frame", &timeStep, 0.01, 0.1);
	ImGui::Checkbox("Enable/Disable", &fixedUpdateEnabled);
	ImGui::End();

	ImGui::Begin("Frame Rate");
	ImGui::SliderInt("frame rate", &frameRate, 5, 1000);
	ImGui::End();

	ImGui::Begin("Wind Resistance");
	ImGui::InputFloat("x amount", &wind.x);
	ImGui::InputFloat("y amount", &wind.y);
	ImGui::InputFloat("z amount", &wind.z);
	ImGui::End();
}

/*
	returns the current value of the timestep for fixedUpdate
	@return float the current value of the timestep
*/
float Simulator::getTimeStep()
{
	return timeStep;
}

/*
	Enables the fixedUpdate for use instead of update
*/
bool Simulator::getFixedUpdateEnabled()
{
	return fixedUpdateEnabled;
}

/*
	gets the current value of the target framerate
	@return int the target framerate
*/
int Simulator::getFrameRate()
{
	return frameRate;
}
