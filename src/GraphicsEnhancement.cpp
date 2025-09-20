/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/19/2025
* SNHU CS499 Computer Science Capstone
* 
* Purpose: 
* This is the entry point to the program, which will setup the necessary libraries and initialize the game context (the window, user inputs, rendering loop)
* 
* Attributions:
* initGLFW() provided by SNHU (no author)
* initGLEW() provided by SNHU (no author)
*/

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>    // "GL extension wranger"
#include <GLFW/glfw3.h> // "graphics library framework," for window cration and input handeling

#include <Context/WindowManager.h>

// predeclare methods
bool initGLFW();
bool initGLEW();

// methods used in this file
const char* WINDOW_TITLE = "SNHU CS499 GRAPHICS ENHANCEMENTS";

int main()
{
	if (!initGLFW()) {
		return EXIT_FAILURE;
	}

	WindowManager* windowManager = new WindowManager();
	GLFWwindow* window = windowManager->CreateDisplayWindow(WINDOW_TITLE);

	if (!initGLEW()) {
		return EXIT_FAILURE;
	}

	while (!glfwWindowShouldClose(window)) {
		// Enable z-depth
		glEnable(GL_DEPTH_TEST);

		// Clear the frame and z buffers
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// convert from 3D object space to 2D view
		//g_ViewManager->PrepareSceneView();

		// refresh the 3D scene
		//g_SceneManager->RenderScene();


		// Flips the the back buffer with the front buffer every frame.
		glfwSwapBuffers(window);

		// query the latest GLFW events
		glfwPollEvents();
	}
}

/**
* try to load GLFW (graphics library framework), which handles window creation and input handeling
* @return false if the library was failed to be loaded
*/
bool initGLFW(){
	// GLFW: initialize and configure library
	// --------------------------------------
	glfwInit();

	#ifdef __APPLE__
		// set the version of OpenGL and profile to use
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#else
		// set the version of OpenGL and profile to use
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif
	// GLFW: end -------------------------------

	return(true);
}

/**
* Try to load GLEW, which is the openGL extension wrangler, which determines whether openGL extenions are supported on the target platform.
* @return false if the library was failed to be loaded
*/
bool initGLEW() {
	// GLEW: initialize
	// -----------------------------------------
	GLenum GLEWInitResult = GLEW_OK;

	// try to initialize the GLEW library
	GLEWInitResult = glewInit();
	if (GLEW_OK != GLEWInitResult)
	{
		std::cerr << glewGetErrorString(GLEWInitResult) << std::endl;
		return false;
	}
	// GLEW: end -------------------------------

	// Displays a successful OpenGL initialization message
	std::cout << "INFO: OpenGL Successfully Initialized\n";
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << "\n" << std::endl;

	return(true);
}
