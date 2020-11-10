#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/types.h>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model {
private:
	std::vector<FTexture> mTexturesLoaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gamaCorrection;

	void loadModel(std::string const &path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<FTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	Model(std::string path, bool gama = false) : gamaCorrection(gama) { loadModel(path);  }
	void Draw(Shader& shader);
	inline std::vector<Mesh> getMeshes() { return meshes; }
	inline std::vector<FTexture> getTextures() { return mTexturesLoaded; }
};

#endif // !MODEL_H