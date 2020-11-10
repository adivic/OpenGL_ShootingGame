#pragma once
#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct FTexture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<FTexture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indecies, std::vector<FTexture> textures);
	void Draw(Shader& shader);

	inline unsigned int getVAO() { return VAO; };

};

#endif // !MESH_H