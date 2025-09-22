/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* The container for all GameObjects.
*/

#include <SceneManagement/Scene.h>
#include <SceneManagement/Mesh.h>
/**
* Constructor.  Set up the camera and the root of the scene
*/
Scene::Scene() {
	activeCamera = new Camera();
	rootNode = new GameObject();

	//TODO remove this line, for testing purposes
	rootNode->addComponent(new Mesh());
}

/**
* get the root gameobject in the scene
*/
GameObject* Scene::getRootGameObject() {
	return rootNode;
}