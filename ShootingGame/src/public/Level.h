#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class Level {
public:
	Level(unsigned int width, unsigned int height, class CameraComponent* playerCamera);
	
	void init();
	void render();

private:
	unsigned int floorVAO, cubeVAO;


	CameraComponent* camera;
	unsigned int Width, Height;
};

#endif // !LEVEL_H
