#include "Game.h"
#include "Level.h"
#include "Utility/Math.h"
#include "Components/Renderer.h"
#include "Scene/Skybox.h"

glm::mat4 Game::defaultProjection = glm::mat4(1.f);

Game::Game(unsigned int width, unsigned int height) : Width(width), Height(height), buttons() { }

Game::~Game() {
	delete player;
	delete level;
	delete renderer;
	delete skybox;
}
unsigned int VBO, VAO;
void Game::init() {
	ResourceManager::loadShader("src/assets/shaders/Texture.vert", "src/assets/shaders/Texture.frag", nullptr, "Texture");
	ResourceManager::loadShader("src/assets/shaders/Model.vert", "src/assets/shaders/Model.frag", nullptr, "Gun");
	ResourceManager::loadShader("src/assets/shaders/muzzleFlash.vert", "src/assets/shaders/muzzleFlash.frag", nullptr, "MuzzleFlash");
	ResourceManager::loadShader("src/assets/shaders/screenTexture.vert", "src/assets/shaders/screenTexture.frag", nullptr, "ScreenTexture");
	ResourceManager::loadShader("src/assets/shaders/skybox.vert", "src/assets/shaders/skybox.frag", nullptr, "Skybox");

	ResourceManager::loadTexture("src/assets/textures/floor.jpg", false, "Floor");
	ResourceManager::loadTexture("src/assets/models/Gun/normal.jpg", false, "Gun");
	ResourceManager::loadTexture("src/assets/textures/container.jpg", false, "Box");
	ResourceManager::loadTexture("src/assets/textures/muzzleFlash.png", true, "MuzzzleFlash");

	/* Setup Uniform buffers */
	unsigned int uniformBlockIndex= glGetUniformBlockIndex(ResourceManager::getShader("Texture").ID, "Matrices");
	unsigned int uniformBlockIndexSky = glGetUniformBlockIndex(ResourceManager::getShader("Skybox").ID, "Matrices");
	glUniformBlockBinding(ResourceManager::getShader("Texture").ID, uniformBlockIndex, 0);
	glUniformBlockBinding(ResourceManager::getShader("Skybox").ID, uniformBlockIndexSky, 0);
	
	glGenBuffers(1, &uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
	

	/* Initialize actors */
	player = new Pawn(glm::vec3(0.f, 0.f, 0.f));
	
	skybox = new SkyBox();

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

	// store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
	glm::mat4 projection = glm::perspective(glm::radians(player->getPlayerCamera()->fov), (float)Width / (float)Height, 0.1f, 100.f);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projection[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//Store view matrix
	glm::mat4 view = player->getPlayerCamera()->getViewMatrix();
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	renderer->renderBegin();

	//Projection matrix for player pawn.
	defaultProjection = glm::perspective(glm::radians(FOV), (float)(Width / Height), .25f, 100.f);
	ResourceManager::getShader("Gun").use().setUnifromMat4f("projection", defaultProjection);
	ResourceManager::getShader("MuzzleFlash").use().setUnifromMat4f("projection", defaultProjection);

	level->render();
	player->render();

	skybox->render();

	renderer->renderEnd();
}
