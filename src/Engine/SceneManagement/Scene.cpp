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
	std::cout << "About to build the demo scene" << std::endl;

	//TODO remove this line, for testing purposes
	rootNode->addComponent(new Mesh("Resources/Meshes/FinalBaseMesh.obj"));
	rootNode->getComponentOfType<Transform>()->xPos = 1;
	rootNode->getComponentOfType<Transform>()->yPos = 1;
	rootNode->getComponentOfType<Transform>()->zPos = 1;
}

/**
* get the root gameobject in the scene
*/
GameObject* Scene::getRootGameObject() {
	return rootNode;
}
