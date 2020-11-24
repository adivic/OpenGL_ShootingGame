#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

class SkyBox {
public:
	unsigned int ID;
	unsigned int Width, Height;
	
	SkyBox();
	~SkyBox();

	void loadCubemap(std::vector<std::string> faces);
	void render();

private:
	unsigned int VAO;
	void init();
};