#include <SceneManagement/GameManager.h>

GameManager::GameManager() {
	renderer = new Renderer();
}

GameManager::~GameManager() {
	renderer = nullptr;
}

// the central loop that application runs from, including rendering, object updates
void GameManager::engineUpdate() {
	onStart();
	onPhysicsUpdate();
	onUpdate();
	render();
}

void GameManager::onStart() {

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