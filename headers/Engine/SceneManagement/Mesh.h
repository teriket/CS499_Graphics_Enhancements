/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* A component that can be attached to gameobjects
* that stores mesh data
*/

#pragma once
#include <SceneManagement/IComponent.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

using namespace std;
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

class Mesh : public IComponent
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	//Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
	Mesh();

private:
	// rendering data
	unsigned int VBO, EBO;

	// setup buffer objects and arrays
	void initMesh();

};

