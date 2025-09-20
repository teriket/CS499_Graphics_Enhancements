#include <Context/InputManager.h>
/**
* singleton instance of this class
*/
InputManager* InputManager::instance = nullptr;

/**
* Constructor.  Gets a reference to the window the applciation lives in.
* TODO: Remove the camera reference from this script.  This is only a temporary
* bandaid fix
*/
InputManager::InputManager() {
	appWindow = WindowManager::getInstance()->getWindow();
	
	bool firstMouseMovement = false;
	double xMousePos = 0;
	double yMousePos = 0;
	double xLastMousePos = 0;
	double yLastMousePos = 0;
	Camera* camera = new Camera();
}


/**
* Destructor.  Release all pointers.
*/
InputManager::~InputManager() {
	instance = nullptr;
}

/**
* access method for the singleton instance of this class.
*/
InputManager* InputManager::getInstance()
{
	if (instance == nullptr) {
		instance = new InputManager();
	}
	return instance;
}


/**
* set callbacks to listen for mouse movements, button clicks, etc.
* Currently, this hardcodes callback behaviors.  Eventually, this
* should be refactored to allow designers to build their own functionality
* i.e. in a gameobject I create a callback to do some behavior whenever
* a certain button is pressed.  For now, this behavior is OK because
* a working prototype needs to get off the ground.
*/
void InputManager::setCallbacks(){
	// this callback is used to receive mouse moving events
	glfwSetCursorPosCallback(appWindow, &InputManager::mousePositionCallback);

	// this callback is used to receive scroll wheel events
	glfwSetScrollCallback(appWindow, &InputManager::scrollWheelCallback);
}

void InputManager::mousePositionCallback(GLFWwindow* window, double xMousePos, double yMousePos) {
	// when the first mouse move event is received, this needs to be recorded so that
// all subsequent mouse moves can correctly calculate the X position offset and Y
// position offset for proper operation
	if (instance->firstMouseMovement)
	{
		instance->xLastMousePos = xMousePos;
		instance->yLastMousePos = yMousePos;
		instance->firstMouseMovement = false;
	}

	// calculate the X offset and Y offset values for moving the 3D camera accordingly
	float xOffset = instance->xMousePos - instance->xLastMousePos;
	float yOffset = instance->yLastMousePos - instance->yMousePos; // reversed since y-coordinates go from bottom to top

	// set the current positions into the last position variables
	instance->xLastMousePos = instance->xMousePos;
	instance->yLastMousePos = instance->yMousePos;

	// move the 3D camera according to the calculated offsets
	instance->camera->ProcessMouseMovement(xOffset, yOffset);
}

void InputManager::scrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset) {
	instance->camera->ProcessMouseScroll(-yOffset);
}

void InputManager::processKeyboardEvents() {

}