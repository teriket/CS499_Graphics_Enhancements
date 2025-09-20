#pragma once
#include <SceneManagement/Transform.h>
class GameObject
{
public:
	Transform transform;
	
	//methods to be overridden from inheriting members
	void onStart() {};
	void onPhysicsUpdate() {};
	void onUpdate() {};

private:

};

