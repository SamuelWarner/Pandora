#include "pch.h"
#include "GameEntity.h"
#include <string>
#include "GUID.h"
#include "LevelManager.h"
/*

DESTRUCTOR needs to not only delete components but remove them from the systems they are subscribed too.

*/

GameEntity::GameEntity(LevelManager* levelManager) : UID(GUID::getID()), lvlManager(levelManager) {};

GameEntity::~GameEntity() {
	for (std::pair<std::string, Component*> element : components) {
		std::string str = element.second->name;
		Component* comp = element.second;
		std::cout << "Deleting Component: " << str << std::endl;
		delete comp;
		lvlManager->removeEntity(this);
		//Component *component = element.second;
		//components.erase(element.first);
		//delete component;
	}
	GUID::returnID(UID);
};

bool GameEntity::addComponent(Component* comp) {
	//if (comp == nullptr) return false;
	assert(comp != nullptr);

	if (components.find(comp->name) == components.end()) {
		comp->parent = this;
		components[comp->name] = comp;
		return true;
	}
	else {
		return false;
	}
};

bool GameEntity::removeComponent(std::string type) {
	std::unordered_map<std::string, Component*>::const_iterator got = components.find(type);
	if (got == components.end()) return false;
	else {
		Component *component = got->second;
		components.erase(got);
		delete component;
		return true;
	}
}

Component* GameEntity::getComponent(std::string compType) {
	std::unordered_map<std::string, Component*>::const_iterator got = components.find(compType);
	if (got == components.end()) return nullptr;
	else return components[compType];
}