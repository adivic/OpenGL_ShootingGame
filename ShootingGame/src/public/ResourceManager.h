#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Texture.h"
#include "Shader.h"
#include <string>
#include <map>

class ResourceManager {
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;

	static Shader loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	static Shader getShader(std::string name);

	static Texture loadTexture(const char* file, bool bAlpha, std::string name);
	static Texture getTexture(std::string name);

	static void clear();

private:
	ResourceManager() {};
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Texture loadTextureFromFile(const char* file, bool bAlpha);
};

#endif // !RESOURCE_MANAGER_H
