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

#include <SceneManagement/GameManager.h>

GameManager::GameManager() {
	// get access to necessary managers 
	renderer = new Renderer();
	inputManager = InputManager::getInstance();
	
	// init variables for time keeping
	time = glfwGetTime();
	lastFrameTime = time;
	deltaTime = 0;

	// TODO: scene management
	currentScene = new Scene();
	renderer->changeScene(currentScene);

	// TODO: When InputManager is refactored, delete this
	// this currently sets up input handeling for mouse events
	inputManager->setCallbacks();
}

/**
* Destructor.  This object should only be destroyed when the application
* closes, so destroy the scene, renderer, and input manager
*/
GameManager::~GameManager() {
	if (renderer != NULL) {
		delete renderer;
	}

	if (currentScene != NULL) {
		delete currentScene;
	}

	if (inputManager != NULL) {
		delete inputManager;
	}
}

/**
* the central loop that application runs from, including rendering, object updates
*/
void GameManager::engineUpdate() {
	onStart();
	handleInputs();
	onPhysicsUpdate();
	onUpdate();
	render();
	setTime();
}

/**
* iterate through every game object in the scene, and activate their onStart()
* method if they haven't been initialized.
*/
void GameManager::onStart() {
	// TODO: Iterate through all objects in the current scene.
	// For each IComponent attached to them, if they've been initialized,
	// pass, otherwise call onStart() for that component
}

void GameManager::handleInputs() {
	// TODO: inputs are handled once, but not every frame.  This code
	// will be refactored, so do that first
	glfwPollEvents();
	inputManager->processKeyboardEvents();
}

/**
* iterate through every gameobject in the active scene and their components,
* and activate their onUpdate() method.
*/
void GameManager::onUpdate() {
	//function stub, to be implemented in Enhancement 2
}

/**
* dispatch the renderManager to draw the scene.
*/
void GameManager::render() {
	if (renderer != nullptr) {
		renderer->draw();
	}
}

/**
* iterate through the scene and update any physics functions
*/
void GameManager::onPhysicsUpdate() {
	//function stub, to be implemented on a future date
}

/**
* @return the length of time the last frame spanned
*/
float GameManager::getDeltaTime() {
	return deltaTime;
}

/**
* @return how long the application has been running
*/
float GameManager::getTime() {
	return time;
}

/**
* update the current time and delta time
*/
void GameManager::setTime() {
	time = glfwGetTime();
	deltaTime = time - lastFrameTime;
	lastFrameTime = time;
}

Scene* GameManager::getActiveScene() {
	return currentScene;
}

/**
* both change the active scene and notify
* the appropriate managers that the scene
* has changed
*/
void GameManager::setScene(Scene* t_scene) {
	delete currentScene; //free memory allocated to current scene

	currentScene = t_scene;

	if (renderer != nullptr) {
		renderer->changeScene(t_scene); // update the scene in the renderer for drawing
	}
}