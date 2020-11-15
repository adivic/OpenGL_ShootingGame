#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
private:
	unsigned int RBO, quadVAO;
	unsigned int Width, Height;

public:
	unsigned int FBO, textureID;

	Renderer(unsigned int width, unsigned int height);
	~Renderer() {}

	void init();
	void update();

	void renderBegin();
	void renderEnd();

};
#endif // !RENDERER_H
