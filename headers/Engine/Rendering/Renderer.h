#pragma once
#include <GLFW/glfw3.h> // "graphics library framework," for window cration and input handeling
#include <Context/WindowManager.h>
#include <Rendering/ShaderManager.h>


class Renderer
{
public:
	void draw();
	void prepareSceneView();

private:
};

