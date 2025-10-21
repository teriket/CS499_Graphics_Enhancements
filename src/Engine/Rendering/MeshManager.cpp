/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* Business logic that handles loading
* and drawing of mesh data stored on a 
* mesh component on a game object
* 
* attributions:
* bindMeshData(), loadModel, and readSubdirectory()
* provided by learnopengl.com/Model-Loading
*/

#include <Rendering/MeshManager.h>

MeshManager* MeshManager::setMesh(Mesh* mesh) {
	this->mesh = mesh;
	return this;
}

/**
* attach normals, texture coordinates, and vertex data to 
* a VAO, VBO, and EBO
*/
MeshManager* MeshManager::bindMeshData() {
	// generate and bind the details the shader will use to render
	// the object.  This must come before VBO binding
	glGenVertexArrays(1, &mesh->VAO);
	glBindVertexArray(mesh->VAO);

	// generate and bind the vertex data itself
	glGenBuffers(1, &mesh->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

	// malloc function for the bound VAO and VBO
	// first argument is buffer type, 
	// then size of array in bytes, 
	// then reference to data, 
	// then "expected usage pattern (GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW)"
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), &mesh->vertices[0], GL_STATIC_DRAW);

	// generate and bind the render order data, then malloc 
	glGenBuffers(1, &mesh->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), &mesh->indices[0], GL_STATIC_DRAW);

	// Setup position:
	glEnableVertexAttribArray(0);
	// How openGL should read this element in the buffer.  
	// First element is index,
	// then number of components per vertex attribute
	// then type of data
	// then whether the data should be clamped between [-1, 1] or [0,1] for signed and unsigned ints
	// then the size of the stride
	// then an offset from the first component in the vertex attribute array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// setup normals: 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// setup texture coords:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

	return this;
}

MeshManager* MeshManager::drawMesh() {

	//draw mesh
	glBindVertexArray(mesh->VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return this;
}

/**
* opens the directory attached to a mesh object, then search each file
* attached to that directory for mesh data
*/
MeshManager* MeshManager::loadModel() {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(mesh->filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return this;
	}
	directory = mesh->filePath.substr(0, mesh->filePath.find_last_of('/'));

	readSubdirectory(scene->mRootNode, scene);

	return this;
}

void MeshManager::readSubdirectory(aiNode* node, const aiScene* scene) {
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		readSubdirectory(node->mChildren[i], scene);
	}

}

/**
* extract the vertices, indices, and texture coordinates from
* a mesh object
*/
Mesh MeshManager::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		// process vertex positions, normals, and texture coordinates
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			vertex.textureCoordinates = glm::vec2(0, 0);
		}

		vertices.push_back(vertex);
	}

	//process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	//process material
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	this->mesh->vertices = vertices;
	this->mesh->indices = indices;
	this->mesh->textures = textures;


	return *this->mesh;
}

std::vector<Texture> MeshManager::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		
		//check if the texture has already been loaded
		for (unsigned int j = 0; j < mesh->loadedTextures.size(); j++) {
			if (std::strcmp( mesh->loadedTextures[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(mesh->loadedTextures[j]);
				skip = true;
				break;
			}
		}

		//texture not loaded, create a new glTexture
		if (!skip) {
			Texture texture;
			texture.textureID = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
		}
	}
	return textures;
}

unsigned int MeshManager::TextureFromFile(const char* path, const std::string& directory) {
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1) {
			format = GL_RED;
		}
		else if (nrComponents == 3) {
			format = GL_RGB;
		}
		else if (nrComponents == 4) {
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Texture data failed to load at path: " << path << std::endl;
	}

	return textureID;

}