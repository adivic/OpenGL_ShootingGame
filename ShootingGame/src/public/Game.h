#pragma once
#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>

class Game {
public:
	unsigned int Width, Height;
	Game(unsigned int width, unsigned int height);
	~Game();

	void init();
	void processInput(GLFWwindow* window, float deltaTime);
	void update(float deltaTime);
	void render();

private:


};
#endif // !GAME_H
