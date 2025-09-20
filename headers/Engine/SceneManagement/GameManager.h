#pragma once
#include <Rendering/Renderer.h>

class GameManager
{
private:
	// private constructor for singleton access
	void onStart();
	void onUpdate();
	void onPhysicsUpdate();
	void render();

	Renderer* renderer = nullptr;

public:
	GameManager();
	~GameManager();
	
	// the central loop that application runs from, including rendering, physics, object updates
	void engineUpdate();

	// COMMENT:
	// Time may eventually need to live in it's own class so it can handle functions
	// like limiting frame rate, slowing or speeding up time, pausing etc.  At this 
	// juncture,the current implementation is OK because there is no need for added
	// complexity to this refactor
	float getDeltaTime();
	float getTime();
};

