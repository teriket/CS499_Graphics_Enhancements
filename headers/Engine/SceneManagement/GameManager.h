/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* The logic that manages the central loop of the
* engine, including updating objects, rendering,
* scene management, user inputs, physics updates.
*/

#pragma once
#include <SceneManagement/Scene.h>
#include <Rendering/Renderer.h>
#include <Context/InputManager.h>

class GameManager
{
public:
	//TODO: Make singleton
	GameManager();
	~GameManager();
	
	Scene* getActiveScene();

	// the central loop that application runs from, including rendering, physics, object updates
	void engineUpdate();
	float getDeltaTime();
	float getTime();

private:
	void onStart();
	void onUpdate();
	void onPhysicsUpdate();
	void render();
	void handleInputs();
	void setTime();
	void setScene(Scene* t_scene);

	Renderer* renderer;
	InputManager* inputManager;
	float time;
	float lastFrameTime;
	float deltaTime;
	Scene* currentScene;
};

