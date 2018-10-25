#pragma once
#include "Vec2.h"
#include <vector>
#include <allegro5/allegro.h>
#include "Structures.h"
#include "System.h"
class GameEntity;

class Component {
public:
	System* subscribed;
	std::string name;
	int UID;
	GameEntity *parent;
	Component() {};
	virtual ~Component() {};
	virtual void update() {};
};

class Health : public Component {
public:
	int hp, maxHp;
	Health(int health, int maxHealth);
	~Health();
	void takeDamage(float amount);
};

class Position : public Component {
public:
	Vec2<float> *position;
	Position(float x, float y);
	~Position();
	void update();
};

class Velocity : public Component {
public:
	float speed;
	Vec2<float> *velocity;
	Velocity(float fSpeed);
	~Velocity();
};

class KeyboardControl : public Component {
public:
	KeyboardControl();
	~KeyboardControl();
	void update();
};

class Sprite : public Component {
public:
	ALLEGRO_BITMAP *sprite = NULL;
	Sprite(const char * filePath);
	~Sprite();
};

class Renderer : public Component {
public:
	Renderer();
	~Renderer();
	void update();
};

class Collision : public Component {
	std::pair<float, float> *xOffset;
	std::pair<float, float> *yOffset;
	bool trigger;
public:
	std::vector<std::pair<std::string, float>> *effects;
	Collision(float leftOffset, float rightOffset, float topOffset, float bottomOffset, bool isTrigger);
	~Collision();
	void update();
	BoundingBox getBoundingBox();
};

