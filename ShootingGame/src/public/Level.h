#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Scene/House.h"

class Level {
public:
	Level(unsigned int width, unsigned int height, class Pawn* playerPawn);
	
	void init();
	void render();

private:
	unsigned int floorVAO, cubeVAO;

	Pawn* player;
	unsigned int Width, Height;
	std::vector<std::unique_ptr<House>> houses;

};

#endif // !LEVEL_H
