#pragma once
#include <SceneManagement/Camera.h>
#include <SceneManagement/GameObject.h>

class Scene
{
public:
	Camera* activeCamera;

private:
	GameObject* rootNode;
};

