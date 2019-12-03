#include "Simulator.h"



Simulator::Simulator(RenderManager * r)
{
	ps = new PhysicsSystem(&world);
	cs = new CollisionSystem(&world);
	rm = r;
	state = State::SETUP;
	rm->switchInputMode();
}


Simulator::~Simulator()
{
}

void Simulator::addBall(glm::vec3 position, float scale)
{
	world.push_back(new Ball(position, scale));
}

void Simulator::addWall(glm::vec3 position, float scale)
{
	world.push_back(new Plane(position, scale));
}

void Simulator::draw(){
	std::cout << world.size() << std::endl;
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
}

void Simulator::update(float deltaTime)
{
	if (state == State::PLAY) {
		cs->update();
		ps->update(deltaTime);
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

void Simulator::menu()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//bool show = true;
	//ImGui::ShowDemoWindow(&show);

	ImGui::Begin("Menu");

	ImGui::InputFloat("x position", &tmpPos.x);
	ImGui::InputFloat("y position", &tmpPos.y);
	ImGui::InputFloat("z position", &tmpPos.z);
	ImGui::SliderFloat("scale", &tmpScale, 1.0f, 10.0f);
	if (ImGui::Button("Add")) {
		addBall(tmpPos, tmpScale);
	}
	if (ImGui::Button("Play")) {
		play();
	}
	if (ImGui::Button("Pause")) {
		pause();
	}
	if (ImGui::Button("Stop")) {
		stop();

	}
	ImGui::End();
}

void Simulator::setup() {
	if (state == State::STOP) {

	}
	else {
		return;
	}
}
