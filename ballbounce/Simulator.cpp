#include "Simulator.h"



Simulator::Simulator(RenderManager * r)
{
	ps = new PhysicsSystem(&world);
	cs = new CollisionSystem(&world);
	rm = r;
	state = State::SETUP;
	rm->switchInputMode();
	world.push_back(new Plane(glm::vec3(0), 200));
}


Simulator::~Simulator()
{
}

void Simulator::addBall(glm::vec3 position, float radius, float mass, float cors)
{
	world.push_back(new Ball(position, radius, mass, cors));
}

void Simulator::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int display_w, display_h;
	glfwGetFramebufferSize(rm->getWindow(), &display_w, &display_h);
	menu();
	for (Entity * e : world) {
		this->rm->draw(e);
	}
	//render imgui
	ImGui::Render();

	glViewport(0, 0, display_w, display_h);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(rm->getWindow());
}

void Simulator::update(float deltaTime)
{
	world.at(0)->setPosition(glm::vec3(0, floorPosition, 0));
	ps->setWind(wind);
	if (state == State::PLAY) {
		cs->update();
		ps->update(deltaTime, freeFall);
	}
}

void Simulator::fixedUpdate()
{
	world.at(0)->setPosition(glm::vec3(0, floorPosition, 0));
	if (state == State::PLAY) {
		cs->update();
		ps->update(this->timeStep, freeFall);
	}
}

void Simulator::play()
{
	state = State::PLAY;
}

void Simulator::pause()
{
	state = State::PAUSE;
}

void Simulator::stop()
{
	state = State::STOP;
	for (Entity * e : world) {
		e->reset();
	}
}

void Simulator::reset() {
	world.clear();
	world.push_back(new Plane(glm::vec3(0), 200));
}

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


	if (ImGui::Button("Add")) {
		addBall(tmpPos, tmpScale, tmpMass, tmpCors);
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

void Simulator::setup() {
	if (state == State::STOP) {

	}
	else {
		return;
	}
}

float Simulator::getTimeStep()
{
	return timeStep;
}

bool Simulator::getFixedUpdateEnabled()
{
	return fixedUpdateEnabled;
}

int Simulator::getFrameRate()
{
	return frameRate;
}
