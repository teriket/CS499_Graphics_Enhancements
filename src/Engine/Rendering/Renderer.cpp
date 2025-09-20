#include <Rendering/Renderer.h>

void Renderer::draw() {
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	// Clear the frame and z buffers
	glClearColor(0.0f, 0.0f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Flips the the back buffer with the front buffer every frame.
	glfwSwapBuffers(WindowManager::getInstance()->getWindow());


	// convert from 3D object space to 2D view
	//g_ViewManager->PrepareSceneView();

	// refresh the 3D scene
	//g_SceneManager->RenderScene();
}

void Renderer::prepareSceneView() {

}