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
#include <filesystem>

/**
* Constructor
*/
Renderer::Renderer() {
	shaderManager = new ShaderManager();
	std::cout << "current working directory: " << std::filesystem::current_path() << std::endl;
	shaderManager->LoadShaders(
		"Resources/Shaders/vertexShader.glsl",
		"Resources/Shaders/fragmentShader.glsl" 
		);
	shaderManager->use();

	meshManager = new MeshManager();
}

/**
* The primary algorithm that renders the scene
*/
void Renderer::draw() {
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	// Clear the frame and z buffers
	glClearColor(0.882f, 0.890f, 0.898f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pushCameraDataToShader();
	findObjectsToBeRendered();
	setupLights();
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
		std::vector<GameObject*> gameObjectsToCheck;
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
	if (shaderManager != nullptr && activeScene != nullptr && activeScene->activeCamera != nullptr) {
		//TODO: move the projection to the camera.  The camera needs to be refactored anyways
		glm::mat4 projection = glm::perspective(
			glm::radians(activeScene->activeCamera->Zoom), 
			(GLfloat)WindowManager::getInstance()->getWindowWidth() / (GLfloat)WindowManager::getInstance()->getWindowHeight(),
			0.1f, 
			100.0f);

		shaderManager->setMat4Value("view", activeScene->activeCamera->GetViewMatrix());
		shaderManager->setMat4Value("projection", projection);
		shaderManager->setVec3Value("viewPosition", activeScene->activeCamera->Position);
	}
}

/**
* load in the mesh data, set the state of the
* shaders to render the texture, material,
* position, rotation, and scale of the object
*/
void Renderer::renderObject() {
	// draw each object that has mesh data attached to it
	for (GameObject* gameObject : objectsToRender) {
		setShaderTransformations(*gameObject->getComponentOfType<Transform>());
		meshManager
			->setMesh(gameObject->getComponentOfType<Mesh>())
			->loadModel()
			->bindMeshData()
			->drawMesh();

			//TODO: refactor mesh code into this algorithm.  Currently, mesh manager
			// is doing all the work, and texture files have to follow certain
			// naming conventions to be drawn

	}
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
* rotation, and scale by converting the data into a 4x4 matrix
*/
void Renderer::setShaderTransformations(Transform transform) {
	if (shaderManager != nullptr) {

		glm::mat4 scale = glm::scale(
			// convert float values into glm vector
			glm::vec3(transform.xScale, transform.yScale, transform.zScale)
		);

		glm::mat4 rotationX = glm::rotate(glm::radians(transform.xRot), glm::vec3(1.0f, 0, 0));
		glm::mat4 rotationY = glm::rotate(glm::radians(transform.yRot), glm::vec3(0, 1.0f, 0));
		glm::mat4 rotationZ = glm::rotate(glm::radians(transform.zRot), glm::vec3(0, 0, 1.0f));
		glm::mat4 translation = glm::translate(glm::vec3(transform.xPos, transform.yPos, transform.zPos));

		glm::mat4 modelView = translation * rotationX * rotationY * rotationZ * scale;

		// send the objects position, scale, and rotation to the shader
		shaderManager->setMat4Value("model", modelView);
	}
}

/**
* Dispatch the MeshManager to setup VBO and VAO objects
*/
void Renderer::setMesh() {}

/**
* send the material data to the shader for rendering
*/
void Renderer::setMaterial() {}

void Renderer::setupLights() {
	std::vector<GameObject*> objects;
	std::vector<Light*> lights;

	// look for all the lights in the scene
	objects.push_back(activeScene->getRootGameObject());
	while (objects.size() > 0) {
		
		std::vector<Light*> object_components = objects[0]->getComponentsOfType<Light>();
		for (Light* light : object_components) {
			lights.push_back(light);
		}
		for (GameObject* child : objects[0]->getChildren()) {
			objects.push_back(child);
		}

		objects.erase(objects.begin());
	}

	//send all the lights to the shader
	for (unsigned int i = 0; i < lights.size(); i++) {
		std::string fieldName = "lightSources[" + std::to_string(i) + "].";
		Transform transform = lights[i]->getParentGameObject()->transform;

		shaderManager->setVec3Value(fieldName + "position", transform.xPos, transform.yPos, transform.zPos);
		shaderManager->setVec3Value(fieldName + "ambientColor", lights[i]->ambientColor[0], lights[i]->ambientColor[1], lights[i]->ambientColor[2]);
		shaderManager->setVec3Value(fieldName + "diffuseColor", lights[i]->diffuseColor[0], lights[i]->diffuseColor[1], lights[i]->diffuseColor[2]);
		shaderManager->setVec3Value(fieldName + "specularColor", lights[i]->specularColor[0], lights[i]->specularColor[1], lights[i]->specularColor[2]);
		shaderManager->setFloatValue(fieldName + "focalStrength", lights[i]->focalStrength);
		shaderManager->setFloatValue(fieldName + "focalStrength", lights[i]->specularIntensity);
	}
}