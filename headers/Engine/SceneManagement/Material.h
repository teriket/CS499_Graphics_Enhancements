/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* ECS component that determines how light
* interacts with a mesh
*/

#pragma once
#include <SceneManagement/IComponent.h>
#include <string>

using namespace std;
class Material : public IComponent
{
public:
	float ambientColor[3]; // the color of the material, even in the dark
	float ambientStrength; // how intensely it should be lit in the "dark"
	float diffuseColor[3]; // The color of the material when light hits it
	float specularColor[3]; // the color of the highlight on a mesh
	float shininess;
	string tag; // the name of this material

private:

};

