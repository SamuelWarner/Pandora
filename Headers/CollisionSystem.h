#pragma once
#include "Components.h"
#include "System.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();
	void update();
	bool CompareBoxes(Collision*, Collision*);
	void handleCollisionEffects(Collision* col1, Collision* col2);
	void handleCollisionPosition(Collision*, Collision*);
	void applyEffect(std::string type, float amount, GameEntity* target);
};

