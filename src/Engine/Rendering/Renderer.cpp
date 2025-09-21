#include <Rendering/Renderer.h>

Renderer::Renderer() {
	//shaderManager = new ShaderManager();
}

void Renderer::draw() {
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	// Clear the frame and z buffers
	glClearColor(0.0f, 0.0f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// convert from 3D object space to 2D view
	//g_ViewManager->PrepareSceneView();

	// refresh the 3D scene
	//g_SceneManager->RenderScene();

	// Flips the the back buffer with the front buffer every frame.
	glfwSwapBuffers(WindowManager::getInstance()->getWindow());


}

void Renderer::drawMesh() {}

//every frame, update camera values
void Renderer::prepareSceneView() {
	//get camera view matrix
	// if shader manager is not null
	//		shaderManager->setMat4Value(viewName, view)
	//		shaderManager->setMat4Value(projectionName, projection)
	//		shaderManager->setVec3Value("viewPosition", camera->position)
}


//every frame for every object
void Renderer::renderScene() {
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