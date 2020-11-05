#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Game::Game(unsigned int width, unsigned int height) : Width(width), Height(height) {}

Game::~Game() {}

void Game::init() {

	//Load Shaders
	//set Shaders unifrms
	//initialize variables 
	// Load textures

}

void Game::processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	/* Camera Movement */
}

void Game::update(float deltaTime) {}

void Game::render() {


}
