#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include "CameraComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ResourceManager.h"

class Game {
public:
	unsigned int Width, Height;
	Game(unsigned int width, unsigned int height);
	~Game();

	void init();
	void processInput(GLFWwindow* window, float deltaTime);
	void update(float deltaTime);
	void render();

	CameraComponent* playerCamera;

private:

};
#endif // !GAME_H
