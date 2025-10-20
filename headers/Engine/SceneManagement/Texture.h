/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* A component that can be attached to Gameobjects
* that stores Texture data
*/

#pragma once
#include <SceneManagement/IComponent.h>
#include <string>

class Texture : public IComponent
{
public:
	unsigned int textureID;
	std::string name;
	std::string path;

	// type of texture, i.e. normal, bump, etc.
	std::string type; // consider converting to enum

private:
};

