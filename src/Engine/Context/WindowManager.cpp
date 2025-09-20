#include <Context/WindowManager.h>

WindowManager::WindowManager() {}

//the static instance of this class
WindowManager* WindowManager::instance = nullptr;

WindowManager::~WindowManager()
{
	this->appWindow = nullptr;
}

WindowManager* WindowManager::getInstance() {
	if (instance == nullptr) {
		instance = new WindowManager();
	}
	return instance;
}

/**
* initial creation of the application window
* @return pointer to the window created
*/
GLFWwindow* WindowManager::createWindow()
{

	// try to create the displayed OpenGL window
	appWindow = glfwCreateWindow(
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_TITLE,
		NULL, NULL);

	if (appWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(appWindow);

	//capture the cursor so it doesn't leave the screen
	glfwSetInputMode(appWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// enable blending for supporting tranparent rendering
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return(appWindow);
}

/**
* returns the window the application lives on, or creates one if it doesn't exist.
*/
GLFWwindow* WindowManager::getWindow() {
	if (this->appWindow == nullptr) {
		return this->createWindow();
	}
	return appWindow;
}

