#pragma once
#include <vector>
#include "GameEntity.h"
#include "tinyxml2.h"
#include "Factory.h"
#include "allegro5/allegro.h"
#include "ControlSystem.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include "LifeSystem.h"

class LevelManager
{
private:
	ComponentFactoryList factories;
	tinyxml2::XMLDocument doc;
public:
	ControlSystem *ctrlSys;
	RenderSystem* renderSys;
	LifeSystem* lifeSys;
	CollisionSystem* collisionSys;
	std::vector<GameEntity*> allEntities;
	LevelManager();
	~LevelManager();
	void loadLevel(int level);
	GameEntity* createEntity(tinyxml2::XMLElement*);
	bool removeEntity(GameEntity*);
};

