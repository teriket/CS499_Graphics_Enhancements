/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* Light component to attach to a Gameobject
*/

#pragma once
#include <SceneManagement/IComponent.h>
class Light : public IComponent
{
public:
	float ambientColor[3]; //base light color, eben in dark spots
	float diffuseColor[3]; //color of directional impact of light
	float specularColor[3]; //color of bright spot from light
	float focalStrength; // how bright the light is
	float specularIntensity; // how sharp the bright spot is


private:
};

