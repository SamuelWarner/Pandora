#include "pch.h"
#include "LifeSystem.h"
#include "GameEntity.h"


LifeSystem::LifeSystem()
{
}


LifeSystem::~LifeSystem()
{
}

void LifeSystem::update() {
	for (size_t i = 0, lenght = subscribers.size(); i < lenght; ++i) {
		Health* health = static_cast<Health*>(subscribers[i]);
		GameEntity* ge = health->parent;
		if (health->hp <= 0) {
			delete ge;
			std::cout << "Kill object!" << std::endl;
		}
	}
}
