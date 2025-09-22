/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* The data structure that keeps a reference
* to all active gameobjects
*/

#pragma once
#include <SceneManagement/Camera.h>
#include <SceneManagement/GameObject.h>

#include <string>
#include <vector>

class Scene
{
public:
	Scene();
	GameObject* getRootGameObject();
	
	Camera* activeCamera;
	string sceneName;
	
private:
	GameObject* rootNode;
};

