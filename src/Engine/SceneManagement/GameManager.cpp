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

	// TODO: When InputManager is refactored, delete this
	// this currently sets up input handeling for mouse events
	inputManager->setCallbacks();
}

GameManager::~GameManager() {
	if (renderer != NULL) {
		renderer = NULL;
	}

	if (currentScene != NULL) {
		currentScene = NULL;
	}
}

// the central loop that application runs from, including rendering, object updates
void GameManager::engineUpdate() {
	onStart();
	handleInputs();
	onPhysicsUpdate();
	onUpdate();
	render();
	setTime();
}

void GameManager::onStart() {
	// TODO: Iterate through all objects in the current scene.
	// For each IComponent attached to them, if they've been initialized,
	// pass, otherwise call onStart() for that component
}

void GameManager::handleInputs() {
	glfwPollEvents();
	inputManager->processKeyboardEvents();
}

void GameManager::onUpdate() {
	//function stub, to be implemented in Enhancement 2
}

void GameManager::render() {
	renderer->draw();
}

void GameManager::onPhysicsUpdate() {
	//function stub, to be implemented on a future date
}

float GameManager::getDeltaTime() {
	return deltaTime;
}

float GameManager::getTime() {
	return time;
}

void GameManager::setTime() {
	time = glfwGetTime();
	deltaTime = time - lastFrameTime;
	lastFrameTime = time;
}

Scene* GameManager::getActiveScene() {
	return currentScene;
}