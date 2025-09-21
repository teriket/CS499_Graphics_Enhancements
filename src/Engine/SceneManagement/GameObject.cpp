#include <SceneManagement/GameObject.h>


GameObject* GameObject::getParent() {
	return parent;
}

vector<GameObject*> GameObject::getChildren() {
	return children;
}

void GameObject::addComponent(IComponent t_component) {
	components.push_back(t_component);
}