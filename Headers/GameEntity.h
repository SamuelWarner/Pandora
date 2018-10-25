#pragma once
#include "Components.h"
#include <unordered_map>
extern class LevelManager;

class GameEntity {
private:
	LevelManager* lvlManager;
protected:
	std::unordered_map<std::string, Component*> components;
public:
	int UID;
	GameEntity(LevelManager* levelManager);
	virtual ~GameEntity();
	bool addComponent(Component*);
	bool removeComponent(std::string);
	Component* getComponent(std::string);
	
};