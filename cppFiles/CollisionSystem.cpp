#include "pch.h"
#include "CollisionSystem.h"
#include "Structures.h"
#include "GameEntity.h"
#include <string>

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update() {
	for (size_t i = 0, lenght = subscribers.size(); i < lenght; ++i) {
		Collision* collider1 = static_cast<Collision*> (subscribers[i]);
		for (Component* comp : subscribers) {
			if (comp->UID != collider1->UID) {
				Collision* collider2 = static_cast<Collision*>(comp);
				bool collision = CompareBoxes(collider1, collider2);
				if (collision) {
					handleCollisionPosition(collider1, collider2);
					handleCollisionEffects(collider1, collider2);
				}
			}
		}
		subscribers[i]->update();
	}
}

bool CollisionSystem::CompareBoxes(Collision* first, Collision* second) {
	BoundingBox main = first->getBoundingBox();
	BoundingBox other = second->getBoundingBox();

	
	if (main.topx > other.botx || other.topx > main.botx) {
		return false;
	}
	if (main.topy > other.boty || other.topy > main.boty) {
		return false;
	}
	std::cout << "Collision Detected!" << std::endl;
	return true;
}

void CollisionSystem::handleCollisionEffects(Collision* col1, Collision* col2) {
	GameEntity* object1 = col1->parent;
	GameEntity* object2 = col2->parent;
	for (const std::pair<std::string, float> &apair : *(col1->effects)) {
		std::cout << "Applying effect: " << apair.first <<  " with a value of: " << apair.second << std::endl;
		applyEffect(apair.first, apair.second, object2);
	}
}

void CollisionSystem::applyEffect(std::string type, float amount, GameEntity* target) {
	if (type == "damage") {
		Health* health = static_cast<Health*>(target->getComponent("Health"));
		if (health != nullptr) health->takeDamage(amount);
	}
}


void CollisionSystem::handleCollisionPosition(Collision* col1, Collision* col2) {
	GameEntity* p = col1->parent;
	Component* comp = col1->parent->getComponent("Velocity");
	if (comp != nullptr) {
		Velocity* vel = static_cast<Velocity*>(comp);
		Position* pos = static_cast<Position*>(col1->parent->getComponent("Position"));
		float velX = vel->velocity->x / 2;
		float velY = vel->velocity->y / 2;
		pos->position->x -= velX;
		pos->position->y -= velY;


		int i = 0;
		while (i < 4) {
			velX /= 2;
			velY /= 2;
			if (CompareBoxes(col1, col2)) {
				pos->position->x -= velX;
				pos->position->y -= velY;
			}
			else {
				pos->position->x += velX;
				pos->position->y += velY;
			}
			i++;
		}
	}
	else {
		if ((comp = col2->parent->getComponent("Velocity")) == nullptr) return;
		Velocity* vel = static_cast<Velocity*>(comp);
		Position* pos = static_cast<Position*>(col2->parent->getComponent("Position"));

		float velX = vel->velocity->x / 2;
		float velY = vel->velocity->y / 2;
		pos->position->x -= velX;
		pos->position->y -= velY;


		int i = 0;
		while (i < 4) {
			velX /= 2;
			velY /= 2;
			if (CompareBoxes(col1, col2)) {
				pos->position->x -= velX;
				pos->position->y -= velY;
			}
			else {
				pos->position->x += velX;
				pos->position->y += velY;
			}
			i++;
		}
	}

	// Call collision resolution code(deal damage, explode, etc) here?
}