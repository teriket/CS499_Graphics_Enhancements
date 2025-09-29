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

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures){
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}
