#pragma once
#include <SceneManagement/Transform.h>
#include <SceneManagement/IComponent.h>
#include <vector>
#include <type_traits>

using namespace std;
class GameObject
{
public:
	// position, rotation, scale
	Transform transform;

	// get the first component of a type attached to an object
	template <typename T>
	T* getComponentOfType() {
		// loop through all the components
		for (IComponent component : components) {
			if (is_same<T, component>::value) {
				// types match, return the component
				return component;
			}
		}
		// no matching type found
		return nullptr;
	};

	// get all components of a type attached to an object
	template <typename T>
	vector<T*> getComponentsOfType() {
		vector<T*> results;
		// loop through all the components
		for (IComponent component : components) {
			if (is_same<T, component>::value) {
				// types match
				results.push_back(component);
			}
		}
		return results;
	}


	template <typename T>
	void removeComponent() {
		// loop through all of this gameobjects components
		for (int i = 0; i < components.size; i++) {
			// check if this is the type of object to be deleted
			if (is_same<T, components.at(i)>::value) {
				// delete the object and stop iterating
				components.erase(components.begin() + i);
				return;
			}
		}
	};

	void addComponent(IComponent t_component);
	
	GameObject* getParent();
	vector<GameObject*> getChildren();


private:
	vector<IComponent> components;

	// Gameobjects live in a tree structure.  Maintain a pointer to parents and children
	GameObject* parent;
	vector<GameObject*> children;

};

