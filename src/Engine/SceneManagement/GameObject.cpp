/** FILE DESCRIPTION
* author: Tanner Hunt
* date: 09/20/2025
* SNHU CS499 Computer Science Capstone
*
* Purpose:
* The container class for the ECS.  Gameobjects
* store a list of components, and each component
* will be updated every frame the engine runs.
*/
#include <SceneManagement/GameObject.h>
GameObject::GameObject() {
	addComponent(new Transform());
}

// destructor.  Deletes all child game objects
GameObject::~GameObject() {
	// delete all child game objects
	for (GameObject* child : children) {
		delete child;
	}
	// delete components
	for (IComponent* component : components) {
		delete component;
	}
}

GameObject* GameObject::getParent() {
	return parent;
}

vector<GameObject*> GameObject::getChildren() {
	return children;
}

void GameObject::addComponent(IComponent* t_component) {
	t_component->setParent(this);
	components.push_back(t_component);
}

GameObject* GameObject::addChild(GameObject* t_child) {
	children.push_back(t_child);
	t_child->parent = this;
	return t_child;
}

vector<IComponent*> GameObject::getComponents() {
	return components;
}