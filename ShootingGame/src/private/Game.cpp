#include "Game.h"
#include "Level.h"
#include "Utility/Math.h"
#include "Components/Renderer.h"

glm::mat4 Game::defaultProjection = glm::mat4(1.f);

Game::Game(unsigned int width, unsigned int height) : Width(width), Height(height), buttons() { }

Game::~Game() {
	delete player;
	delete level;
	delete renderer;
}
unsigned int VBO, VAO;
void Game::init() {
	ResourceManager::loadShader("src/assets/shaders/Texture.vert", "src/assets/shaders/Texture.frag", nullptr, "Texture");
	ResourceManager::loadShader("src/assets/shaders/Model.vert", "src/assets/shaders/Model.frag", nullptr, "Gun");
	ResourceManager::loadShader("src/assets/shaders/muzzleFlash.vert", "src/assets/shaders/muzzleFlash.frag", nullptr, "MuzzleFlash");
	ResourceManager::loadShader("src/assets/shaders/screenTexture.vert", "src/assets/shaders/screenTexture.frag", nullptr, "ScreenTexture");

	ResourceManager::loadTexture("src/assets/textures/floor.jpg", false, "Floor");
	ResourceManager::loadTexture("src/assets/models/Gun/normal.jpg", false, "Gun");
	ResourceManager::loadTexture("src/assets/textures/container.jpg", false, "Box");
	ResourceManager::loadTexture("src/assets/textures/muzzleFlash.png", true, "MuzzzleFlash");

	player = new Pawn(glm::vec3(0.f, 0.f, 0.f));

	renderer = new Renderer(Width, Height, player);
	renderer->init();
	
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
	//Aiming
	if (buttons[GLFW_MOUSE_BUTTON_RIGHT] && !buttonsPressed[GLFW_MOUSE_BUTTON_RIGHT]) {
		player->bAiming = true;
		buttonsPressed[GLFW_MOUSE_BUTTON_RIGHT] = true;
	}
	// Stop aiming
	if (!buttons[GLFW_MOUSE_BUTTON_RIGHT] && !buttonsPressed[GLFW_MOUSE_BUTTON_RIGHT])
		player->bAiming = false;
	//Sprinting
	if (buttons[GLFW_KEY_LEFT_SHIFT] && !buttonsPressed[GLFW_KEY_LEFT_SHIFT] && !player->bSprinting) {
		player->sprint(true);
		buttonsPressed[GLFW_KEY_LEFT_SHIFT] = true;
	} 
	// Sprint stop
	if (!buttons[GLFW_KEY_LEFT_SHIFT] && !buttonsPressed[GLFW_KEY_LEFT_SHIFT] && player->bSprinting)
		player->sprint(false);
	//Firing
	if (buttons[GLFW_MOUSE_BUTTON_LEFT] && !buttonsPressed[GLFW_MOUSE_BUTTON_LEFT] && !player->bSprinting) { // semi fire
		player->fire();
		buttonsPressed[GLFW_MOUSE_BUTTON_LEFT] = true;
	}
	//reload
	if (buttons[GLFW_KEY_R] && !buttonsPressed[GLFW_KEY_R]) {
		player->getWeapon()->reload();
		buttonsPressed[GLFW_KEY_R] = true;
	}
	// jumping
	//if (buttons[GLFW_KEY_SPACE] && !buttonsPressed[GLFW_KEY_SPACE] && player->bCanJump) {
	//	player->processMovement(EMovement::UP, deltaTime);
	//	player->bCanJump = false;
	//	player->bJumping = true;
	//	buttonsPressed[GLFW_KEY_SPACE] = true;
	//}
	//if (buttons[GLFW_KEY_SPACE] && buttonsPressed[GLFW_KEY_SPACE] )
	//	player->bCanJump = true;
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
	renderer->renderBegin();

	defaultProjection = glm::perspective(glm::radians(FOV), (float)(Width / Height), .25f, 100.f);
	ResourceManager::getShader("Gun").use().setUnifromMat4f("projection", defaultProjection);
	ResourceManager::getShader("MuzzleFlash").use().setUnifromMat4f("projection", defaultProjection);

	level->render();
	player->render();

	renderer->renderEnd();
}
