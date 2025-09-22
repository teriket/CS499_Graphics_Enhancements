/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* Overseer for the entirety of the rendering process
* Searches for objects to be rendered, then dispatches
* the mesh manager, texture manager, material manager
* and shader manager to draw the object to the screen.
* 
*/

#include <Rendering/Renderer.h>

/**
* Constructor
*/
Renderer::Renderer() {
	shaderManager = new ShaderManager();
}

/**
* The primary algorithm that renders the scene
*/
void Renderer::draw() {
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	// Clear the frame and z buffers
	glClearColor(0.0f, 0.0f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	findObjectsToBeRendered();
	pushCameraDataToShader();
	renderObject();

	// Flips the the back buffer with the front buffer every frame.
	glfwSwapBuffers(WindowManager::getInstance()->getWindow());

}

/**
* perform breadth first search of the entire scene for any
* objects with a Mesh component attached to them.  Those
* are the items that will be rendered.  They may not necessarily
* have a material or texture attached to them.
*/
void Renderer::findObjectsToBeRendered() {
	if (activeScene != nullptr) {
		// gameobjects are created and destroyed, possibly every frame
		// start with a fresh list of things to render every frame
		objectsToRender.clear();
		
		// list of gameobjects to check for a breadth-first search of the scene
		vector<GameObject*> gameObjectsToCheck;		
		gameObjectsToCheck.push_back(activeScene->getRootGameObject());

		//breadth first search
		while (gameObjectsToCheck.size() > 0) {
			// null pointers shouldn't be able to make their way in here, but it doesnt hurt to check
			if (gameObjectsToCheck.at(0) != nullptr) {
				GameObject* currentObject = gameObjectsToCheck.at(0);

				// check if the current gameobject has any meshes to render
				if (currentObject->getComponentsOfType<Mesh>().size() > 0) {
					// this object has a mesh to be rendered.  Add it to the list.
					objectsToRender.push_back(currentObject);
				}

				//put the current gameobjects children into the set of items to be checked
				for (GameObject* child : currentObject->getChildren()) {
					gameObjectsToCheck.push_back(child);
				}

				//remove this gameobject from the list of items to be checked
				gameObjectsToCheck.erase(gameObjectsToCheck.begin());
			}
			// The first index of the breadth first search was a nullptr.  Remove it and continue
			else {
				gameObjectsToCheck.erase(gameObjectsToCheck.begin());
			}
		}
		

	}
}

void Renderer::changeScene(Scene* t_scene) {
	activeScene = t_scene;
}

/**
* updates the shader to the position, rotation, FOV, and projection
* the camera is using
*/
void Renderer::pushCameraDataToShader() {
	//PSEUDOCODE based on old projects algorithm
	//get camera view matrix
	// if shader manager is not null
	//		shaderManager->setMat4Value(viewName, view)
	//		shaderManager->setMat4Value(projectionName, projection)
	//		shaderManager->setVec3Value("viewPosition", camera->position)
}

/**
* load in the mesh data, set the state of the
* shaders to render the texture, material,
* position, rotation, and scale of the object
*/
void Renderer::renderObject() {
	// draw each object that has mesh data attached to it
	for (GameObject* gameObject : objectsToRender) {
			// mesh may have none or one material attached to it
			
			// Mesh may have no, one, or multiple textures attached to it
			
			// manage the transform
			
			// render the mesh

	}
	// PSUEDOCODE based on old projects code
	//foreach object in scene
	//glm::vec3 scaleXYZ
	//float xrotation degrees
	//float yrotation degrees
	//float zrotation degrees
	//position xyz
	//SetTransformations()
	//setShaderTexture
	//setTextureUVscale
	//setShaderMaterial()
	//mesh->draw()
};

/**
* Dispatch the Texture manager to correctly
* setup a texture on the given mesh
*/
void Renderer::setShaderTexture() {}

/**
* Update the shader so the correct material
* renders on the mesh
*/
void Renderer::setShaderMaterial() {

}

/**
* Update the shader to reflect the meshes position,
* rotation, and scale
*/
void Renderer::setSahderTransformations() {}

/**
* Dispatch the MeshManager to setup VBO and VAO objects
*/
void Renderer::setMesh() {}

/**
* send the material data to the shader for rendering
*/
void Renderer::setMaterial() {}