/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* The primary thread the application runs on.  This code
* manages the loop of updating the scene, accepting user
* inputs, and rendering.  The context of the application
* also lives here, including the time and active scene.
*
*/

#pragma once
#include <SceneManagement/Scene.h>
#include <Rendering/Renderer.h>
#include <Context/InputManager.h>

class GameManager
{
private:
	// private constructor for singleton access
	void onStart();
	void onUpdate();
	void onPhysicsUpdate();
	void render();
	void handleInputs();
	void setTime();

	Renderer* renderer;
	InputManager* inputManager;
	float time;
	float lastFrameTime;
	float deltaTime;
	Scene* currentScene;

public:
	GameManager();
	~GameManager();
	
	Scene* getActiveScene();

	// the central loop that application runs from, including rendering, physics, object updates
	void engineUpdate();
	float getDeltaTime();
	float getTime();
};

