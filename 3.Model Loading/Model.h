#pragma once
#include <vector>
#include "Mesh.h"
#include <string>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include <iostream>
#include "Shader.h"

class Model
{
public:
	Model(std::string  path);
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
	void Draw(Shader* shader);
private:
	void loadModel(std::string  path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory);
};

