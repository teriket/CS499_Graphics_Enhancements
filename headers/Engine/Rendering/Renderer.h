#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> // "graphics library framework," for window cration and input handeling
#include <Context/WindowManager.h>
#include <Rendering/ShaderManager.h>


class Renderer
{
public:
	Renderer();
	void draw();

	//old methods for rendering
	void prepareSceneView();
	void renderScene();

private:
	void drawMesh();
	ShaderManager* shaderManager;
};

