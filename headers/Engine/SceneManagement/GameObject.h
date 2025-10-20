#pragma once
#include <SceneManagement/Transform.h>

#include <vector>
#include <typeinfo>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

class IComponent;
class GameObject
{
public:
	~GameObject();
	GameObject();
	// position, rotation, scale
	Transform transform;

	// get the first component of a type attached to an object
	template <typename T>
	T* getComponentOfType() {
		for (IComponent* component : components) {
			// To test whether the types are the same, try to make a type T object that
			// is casted to the component.  It will generate a nullptr if the types are
			// not related
			if (T * casted = dynamic_cast<T*>(component)) {
				return casted;
			}
		}
		return nullptr;
	}

	// get all components of a type attached to an object
	template <typename T>
	std::vector<T*> getComponentsOfType() {
		std::vector<T*> results;
		// loop through all the components
		for (IComponent* component : components) {
			// To test whether the types are the same, try to make a type T object that
			// is casted to the component.  It will generate a nullptr if the types are
			// not related
			if (T* casted = dynamic_cast<T*>(component)) {
				results.push_back(casted);
			}
		}
		return results;
	}

	void addComponent(IComponent* t_component);
	
	GameObject* getParent();
	std::vector<GameObject*> getChildren();
	GameObject* addChild(GameObject* t_child);
	std::vector<IComponent*> getComponents();
	int getDepth();
	void setDepth();
	void setParent(GameObject* t_parent);

private:
	std::vector<IComponent*> components;

	// Gameobjects live in a tree structure.  Maintain a pointer to parents and children
	GameObject* parent;
	std::vector<GameObject*> children;

	// how deep in the scene tree this object is
	int depth = 0;
	// Deeply nested objects risks stack overflow exceptions when sharing levels between users.
	// 256 is a generous depth that isn't expected to be reached in a scene
	// except by malicious users attempting such an attack
	const int MAX_OBJECT_DEPTH = 256;
};

