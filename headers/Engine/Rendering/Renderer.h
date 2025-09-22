/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/21/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* Overseer for the entirety of the rendering process
* Searches for objects to be rendered, then dispatches
* the appropriate mesh manager, texture manager, material
* manager, and shader manager to draw the object to the
* screen.
*/

#pragma once
#include <GL/glew.h> // glew is a diva and will throw errors if it's not included before GLFW, even if it isn't being used
#include <GLFW/glfw3.h> // "graphics library framework," for window cration and input handeling
#include <Context/WindowManager.h>

// managers that the Renderer dispatches tasks to
#include <Rendering/ShaderManager.h>
#include <Rendering/MeshManager.h>
#include <Rendering/TextureManager.h>

// the components the renderer checks that gameobject have
#include <SceneManagement/Mesh.h>
#include <SceneManagement/Texture.h>
#include <SceneManagement/Material.h>

#include <SceneManagement/Scene.h>

#include <vector>

using namespace std;
class Renderer
{
public:
	Renderer();
	void draw();
	void changeScene(Scene* t_scene);

	void pushCameraDataToShader();
	void renderObject();

private:
	ShaderManager* shaderManager;
	Scene* activeScene;
	vector<GameObject*> objectsToRender;

	// searches the current scene for any object with a mesh component
	void findObjectsToBeRendered();

	// update the state of the shader so that it draws an object with the following
	// textures, material, mesh, and transformation
	void setShaderTexture();
	void setShaderMaterial();
	void setSahderTransformations();
	void setMesh();
	void setMaterial();

};

