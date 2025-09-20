/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* This code is responsible for creating and maintaining the window from which the application takes place.
*
*/
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <iostream>
#include "GLFW/glfw3.h"  // library that manages window creation

class WindowManager
{
public:
	//destructor
	~WindowManager();

	//singleton access for this class
	static WindowManager* getInstance();

	//checks whether a window exists for this app, and
	//creates one if it doesn't.  Returns the app window
	GLFWwindow* getWindow();

private:
	//constructor private for singleton access
	WindowManager();

	//this method is called when a window does not exist
	GLFWwindow* createWindow();

	// the active OpenGL display window
	GLFWwindow* appWindow;
	// singleton instance of this class
	static WindowManager* instance;

	const char* WINDOW_TITLE = "CS499 Graphics Enhancements";
	const int WINDOW_WIDTH = 1000;
	const int WINDOW_HEIGHT = 800;
};

#endif