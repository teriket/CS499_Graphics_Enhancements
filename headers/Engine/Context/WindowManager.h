/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* This code is responsible for creating and maintaining the window from which the application takes place.
*
*/
#pragma once

#include <iostream>
#include "GLFW/glfw3.h"  // library that manages window creation

class WindowManager
{
public:
	// constructor & destructor
	WindowManager();
	~WindowManager();

private:
	// active OpenGL display window
	GLFWwindow* app_window;

public:
	// create the initial OpenGL display window
	GLFWwindow* CreateDisplayWindow(const char* windowTitle);

};