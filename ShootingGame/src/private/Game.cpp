#include "Game.h"
#include "Level.h"
#include "Utility/Math.h"

Game::Game(unsigned int width, unsigned int height) : Width(width), Height(height), buttons() { }

Game::~Game() {
	delete player;
	delete level;
}
unsigned int VBO, VAO;
void Game::init() {
	ResourceManager::loadShader("src/assets/shaders/Texture.vert", "src/assets/shaders/Texture.frag", nullptr, "Texture");
	ResourceManager::loadShader("src/assets/shaders/Model.vert", "src/assets/shaders/Model.frag", nullptr, "Gun");

	ResourceManager::loadTexture("src/assets/textures/floor.jpg", false, "Floor");
	ResourceManager::loadTexture("src/assets/textures/container.jpg", false, "Box");

	player = new Pawn(glm::vec3(0.f, 0.f, 0.f));
	
	level = new Level(Width, Height, player);
	level->init();
	
}

void Game::processInput(float deltaTime) {
	if (buttons[GLFW_KEY_W]) 
		player->processMovement(EMovement::FORWARD, deltaTime);
	if (buttons[GLFW_KEY_A]) 
		player->processMovement(EMovement::LEFT, deltaTime);
	if (buttons[GLFW_KEY_S]) 
		player->processMovement(EMovement::BACKWARD, deltaTime);
	if (buttons[GLFW_KEY_D]) 
		player->processMovement(EMovement::RIGHT, deltaTime);
	if (buttons[GLFW_MOUSE_BUTTON_RIGHT] && !buttonsPressed[GLFW_MOUSE_BUTTON_RIGHT]) {
		player->bAiming = true;
		buttonsPressed[GLFW_MOUSE_BUTTON_RIGHT] = true;
	}
	if (!buttons[GLFW_MOUSE_BUTTON_RIGHT] && !buttonsPressed[GLFW_MOUSE_BUTTON_RIGHT])
		player->bAiming = false;
}

void Game::update(float deltaTime) {
	//TODO: Apply gravity
	
	player->update(deltaTime);
	// Player Aiming Smooth
	float Fov = player->bAiming ? 15.f : FOV;
	float NewFov = Math::InterpTo(player->getPlayerCamera()->fov, Fov, deltaTime, 15.f);
	player->getPlayerCamera()->fov = NewFov;
}

void Game::render() {
	glm::mat4 projection = glm::perspective(glm::radians(FOV), (float)(Width / Height), .1f, 100.f);
	ResourceManager::getShader("Gun").use().setUnifromMat4f("projection", projection);

	level->render();
	player->render();
}
