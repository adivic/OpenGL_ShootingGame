#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Pawn.h"
#include "ResourceManager.h"

constexpr float GRAVITY = 9.81f;

class Game {
public:
	unsigned int Width, Height;
	bool buttons[1024];
	bool buttonsPressed[1024];
	static glm::mat4 defaultProjection;

	Game(unsigned int width, unsigned int height);
	~Game();

	void init();
	void processInput(float deltaTime);
	void update(float deltaTime);
	void render();

	Pawn* player;

private:
	unsigned int uboMatrices;
	class Level* level;
	class Renderer* renderer;
};
#endif // !GAME_H
