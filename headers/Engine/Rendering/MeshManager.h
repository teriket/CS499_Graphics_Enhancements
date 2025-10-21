/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* Business logic that handles loading
* and drawing of mesh data stored on a
* mesh component.  This is a state machine,
* so first load the mesh into the object,
* then subsequent function calls will
* operate on that object.
*/
#include <SceneManagement/Mesh.h>
#include <SceneManagement/Texture.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include <iostream>
#include <vector>
#include <string>

#pragma once
class MeshManager
{
public:
	MeshManager* setMesh(Mesh* mesh);
	MeshManager* loadModel();
	MeshManager* bindMeshData();
	MeshManager* drawMesh();
	

private:
	Mesh* mesh;

	std::string directory;
	std::vector<Mesh> meshes;

	void readSubdirectory(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory);
};

