#include "Game.h"
#include "Level.h"

Level* level;

Game::Game(unsigned int width, unsigned int height) : Width(width), Height(height) { }

Game::~Game() {
	delete playerCamera;
	delete level;
}
unsigned int VBO, VAO;
void Game::init() {

	playerCamera = new CameraComponent(glm::vec3(0.f, 0.f, 0.f));
	
	ResourceManager::loadShader("src/assets/shaders/Texture.vert", "src/assets/shaders/Texture.frag", nullptr, "Texture");

	ResourceManager::loadTexture("src/assets/textures/floor.jpg", false, "Floor");
	ResourceManager::loadTexture("src/assets/textures/container.jpg", false, "Box");

	level = new Level(Width, Height, playerCamera);
	level->init();
}

void Game::processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	/* Camera Movement */
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		playerCamera->processMovement(EMovement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		playerCamera->processMovement(EMovement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		playerCamera->processMovement(EMovement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		playerCamera->processMovement(EMovement::LEFT, deltaTime);
}

void Game::update(float deltaTime) {
	
}

void Game::render() {
	level->render();
}
