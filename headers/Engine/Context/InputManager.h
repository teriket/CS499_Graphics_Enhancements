/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* provides an interface for gameobjects to receive
* user input data
*/

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Context/WindowManager.h>
#include <SceneManagement/Camera.h>

class InputManager
{
public:
	~InputManager();
	static InputManager* getInstance();
	void setCallbacks();

	static void mousePositionCallback(GLFWwindow* window, double xMousePos, double yMousePos);
	static void scrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset);
	void processKeyboardEvents();

private:
	InputManager();
	static InputManager* instance;
	GLFWwindow* appWindow;
	
	// TODO: refactor this code out of input handeler.  As described
	// above, this is only temporarily being stored in input handeler
	// just to get the code running.  Input handeler SHOULD NOT be 
	// responsible for tracking all this, and will eventually be
	// refactored.  Below is handeling for camera movements
	Camera* camera;
	bool firstMouseMovement;
	double xMousePos;
	double yMousePos;
	double xLastMousePos;
	double yLastMousePos;

};