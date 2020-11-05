#include "ResourceManager.h"
#include <fstream>
#include <sstream>

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;

Shader ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::getShader(std::string name) {
	return Shaders[name];
}

Texture ResourceManager::loadTexture(const char* file, bool bAlpha, std::string name) {
	Textures[name] = loadTextureFromFile(file, bAlpha);
	return Textures[name];
}

Texture ResourceManager::getTexture(std::string name) {
	return Textures[name];
}

void ResourceManager::clear() {
	for (auto it : Shaders)
		glDeleteProgram(it.second.ID);
	for (auto it : Textures)
		glDeleteTextures(1, &it.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try {
		std::ifstream vsFile(vShaderFile);
		std::ifstream fsFile(fShaderFile);
		std::stringstream vsStream, fsStream;
		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();
		vsFile.close();
		fsFile.close();

		vertexCode = vsStream.str();
		fragmentCode = fsStream.str();
		if (gShaderFile) {
			std::ifstream gsFile(gShaderFile);
			std::stringstream gsStream;
			gsStream << gsFile.rdbuf();
			gsFile.close();
			geometryCode = gsStream.str();
		}
	} catch (std::exception& e) {
		std::cout << "[ERROR SHADER]: Failed to read shader files\n";
	}
	const char* vsCode = vertexCode.c_str();
	const char* fsCode = fragmentCode.c_str();
	const char* gsCode = geometryCode.c_str();
	Shader shader;
	shader.compile(vsCode, fsCode, gShaderFile ? gsCode : nullptr);
	return shader;
}

Texture ResourceManager::loadTextureFromFile(const char* file, bool bAlpha) {
	Texture texture;
	if (bAlpha) {
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}
	int width, height, nrChannels;
	auto data = stbi_load(file, &width, &height, &nrChannels, 0);
	texture.generate(width, height, data);
	stbi_image_free(data);
	return texture;
}
