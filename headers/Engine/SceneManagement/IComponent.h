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
class IComponent
{
	virtual void onStart() {};
	virtual void onUpdate() {};
	virtual void onPhysicsUpdate() {};
};

