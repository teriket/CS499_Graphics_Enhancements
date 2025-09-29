#pragma once
#include <SceneManagement/Transform.h>
#include <SceneManagement/IComponent.h>
#include <vector>
#include <typeinfo>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
class GameObject
{
public:
	~GameObject();
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
	vector<T*> getComponentsOfType() {
		vector<T*> results;
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
	vector<GameObject*> getChildren();
	GameObject* addChild(GameObject* t_child);
	vector<IComponent*> getComponents();

private:
	vector<IComponent*> components;

	// Gameobjects live in a tree structure.  Maintain a pointer to parents and children
	GameObject* parent;
	vector<GameObject*> children;

};

