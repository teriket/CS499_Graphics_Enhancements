/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* A component that can be attached to gameobjects
* that stores vertex, line, and face data of a mesh
*/

#pragma once
#include <SceneManagement/IComponent.h>
#include <SceneManagement/Texture.h>

// vertex binding and vertex array object binding
#include <GL/glew.h>

// math libraries
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

// standard library imports
#include <vector>
#include <string>


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

class Mesh : public IComponent
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::vector<Texture> loadedTextures;
	std::string filePath;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh(std::string path);

	// rendering data: vertex buffer object (VBO) contains arrays
	// of vertex data.  Vertex array objects (VAO) contains details
	// about the VBO for the shader, element buffer object (EBO)
	// stores indices to vertices
	unsigned int VAO, VBO, EBO;

};

