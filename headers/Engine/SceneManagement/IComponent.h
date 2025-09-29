/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* The base class all game functionality should
* be attached to for the ECS.  
*/

#pragma once
class GameObject;
class IComponent
{
public:
	virtual void onStart() {};
	virtual void onUpdate() {};
	virtual void onPhysicsUpdate() {};
	
	
	virtual GameObject* getParentGameObject() {
		return parent;
	}

	virtual void setParent(GameObject* go) {
		parent = go;
	}

	bool onStart_was_called = false;
	GameObject* parent = nullptr;
};

