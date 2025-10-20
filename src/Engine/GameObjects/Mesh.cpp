/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* A component that can be attached to a game object
* that stores mesh data.  Any game object with a mesh
* component will be rendered.
*/

#include <SceneManagement/Mesh.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}

Mesh::Mesh(std::string path) {
	this->filePath = path;
}
