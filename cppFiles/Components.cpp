#pragma once
#include "pch.h"
#include "Components.h"
#include "GameEntity.h"
#include "Vec2.h"
#include <vector>
#include <allegro5/allegro.h>
#include "global.h"
#include "GUID.h"


Health::Health(int health, int maxHealth) : hp(health), maxHp(maxHealth) { name = "Health"; UID = GUID::getID(); };
Health::~Health() { 
	if (subscribed != nullptr) subscribed->removeComponent(this); 
	GUID::returnID(UID); 
}
void Health::takeDamage(float amount) {
	hp -= amount;
	std::cout << "Health now at: " << hp << std::endl;
}

Position::Position(float x, float y) { name = "Position"; position = new Vec2<float>(x, y); UID = GUID::getID(); };
Position::~Position() { 
	if (subscribed != nullptr) subscribed->removeComponent(this); 
	delete position; 
	GUID::returnID(UID); 
}
void Position::update() {
	Velocity *vel = static_cast<Velocity*>(parent->getComponent("Velocity"));
	if (vel != NULL) {
		position->x += vel->velocity->x;
		position->y += vel->velocity->y;
	}
}

Velocity::Velocity(float fSpeed) : speed(fSpeed) { name = "Velocity"; velocity = new Vec2<float>(0, 0); UID = GUID::getID(); };
Velocity::~Velocity() { 
	if (subscribed != nullptr) subscribed->removeComponent(this);   
	delete velocity; 
	GUID::returnID(UID); 
};

KeyboardControl::KeyboardControl() { name = "KeyboardControl"; UID = GUID::getID(); };
KeyboardControl::~KeyboardControl() {
	if(subscribed!=nullptr) subscribed->removeComponent(this); 
	GUID::returnID(UID); 
}
void KeyboardControl::update() {
	Velocity *vel = static_cast<Velocity*>(parent->getComponent("Velocity"));
	if (vel != nullptr) {
		vel->velocity->x = 0;
		vel->velocity->y = 0;
		if (global::keys[ALLEGRO_KEY_RIGHT]) vel->velocity->x = vel->speed;
		if (global::keys[ALLEGRO_KEY_LEFT]) vel->velocity->x = -vel->speed;
		if (global::keys[ALLEGRO_KEY_UP]) vel->velocity->y = -vel->speed;
		if (global::keys[ALLEGRO_KEY_DOWN]) vel->velocity->y = vel->speed;
	}
};

Sprite::Sprite(const char * filePath) {	name = "Sprite"; sprite = al_load_bitmap(filePath); UID = GUID::getID(); };
Sprite::~Sprite() {
	if (subscribed != nullptr) subscribed->removeComponent(this); 
	al_destroy_bitmap(sprite); 
	GUID::returnID(UID); 
}

Renderer::Renderer() { name = "Renderer"; UID = GUID::getID(); };
Renderer::~Renderer() { 
	if (subscribed != nullptr) subscribed->removeComponent(this); 
	GUID::returnID(UID); 
}
void Renderer::update() {
	Position* pos = static_cast<Position*>(parent->getComponent("Position"));
	al_draw_bitmap(static_cast<Sprite*>(parent->getComponent("Sprite"))->sprite,
		pos->position->x,
		pos->position->y,
		0);
}

Collision::Collision(float leftOffset, float rightOffset, float topOffset, float bottomOffset, bool isTrigger) { 
	trigger = isTrigger;
	xOffset = new std::pair<float, float>(leftOffset, rightOffset);
	yOffset = new std::pair<float, float>(topOffset, bottomOffset);
	effects = new std::vector<std::pair<std::string, float>>();
	name = "Collision"; 
	UID = GUID::getID(); 
}
Collision::~Collision() { 
	if (subscribed != nullptr) subscribed->removeComponent(this);

	delete effects;
	delete yOffset;
	delete xOffset;
	
	GUID::returnID(UID); 
}
void Collision::update() {};


BoundingBox Collision::getBoundingBox() {
	BoundingBox output;
	ALLEGRO_BITMAP* img = static_cast<Sprite*>(parent->getComponent("Sprite"))->sprite;
	assert(img != nullptr);
	Position* pos = static_cast<Position*>(parent->getComponent("Position"));
	assert(pos != nullptr);
	int w = al_get_bitmap_width(img);
	int h = al_get_bitmap_height(img);
	
	// Check for errors in offset amounts. Offset should never drive the values negative or invert the bounding box;
	output.topx = pos->position->x + (w * xOffset->first);
	output.topy = pos->position->y + (h * yOffset->first);
	output.botx = pos->position->x + (w - (w * xOffset->second));
	output.boty = pos->position->y + (h - (h * yOffset->second));
	
	//std::vector<std::pair<float, float>> output(4);
	//std::pair<float, float> p(0 + w * xOffset.first, 0 + h * yOffset.first); 
	//output[0] = std::pair<float, float>(pos->position->x + (w * xOffset->first), pos->position->y + (h * yOffset->first)); //top left corner
	//output[1] = std::pair<float, float>(pos->position->x + (w - (w * xOffset->second)), pos->position->y + (h * yOffset->first)); //top right corner
	//output[2] = std::pair<float, float>(pos->position->x + (w * xOffset->first), pos->position->y + (h - (h * yOffset->second))); //bottem left corner
	//output[3] = std::pair<float, float>(pos->position->x + (w - (w * xOffset->second)), pos->position->y + (h - (h * yOffset->second))); //bottem right corner

	return output;
}