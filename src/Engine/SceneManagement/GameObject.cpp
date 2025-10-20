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
#include <SceneManagement/IComponent.h>
#include <SceneManagement/Transform.h>

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

std::vector<GameObject*> GameObject::getChildren() {
	return children;
}

void GameObject::addComponent(IComponent* t_component) {
	t_component->setParent(this);
	components.push_back(t_component);
}

GameObject* GameObject::addChild(GameObject* t_child) {
	// don't let objects become deeply nested for security purposes
	if (depth >= MAX_OBJECT_DEPTH) {
		std::cout << "cannot create deeply-nested objects" << std::endl;
		return nullptr;
	}

	children.push_back(t_child);
	t_child->setParent(this);
	return t_child;
}

std::vector<IComponent*> GameObject::getComponents() {
	return components;
}

int GameObject::getDepth() {
	return depth;
}

void GameObject::setDepth() {
	if (parent != nullptr) {
		depth = parent->getDepth() + 1;
		
		// update the depth of all child gameobjects
		for (GameObject* child : children) {
			child->setDepth();
		}
	}
	// this is the root gameobject, and has depth 0
	else {
		depth = 0;
	}
}

void GameObject::setParent(GameObject* t_parent) {
	// don't let objects become deeply nested for security purposes
	if (t_parent->getDepth() >= MAX_OBJECT_DEPTH) {
		std::cout << "cannot create deeply-nested objects" << std::endl;
		return;
	}

	this->parent = t_parent;
	this->setDepth();
}
