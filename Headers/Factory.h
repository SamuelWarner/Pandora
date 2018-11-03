#pragma once
#include "Components.h"
#include "tinyxml2.h"
#include <unordered_map>
class LevelManager;

class IFactory
{
protected:
	LevelManager* lm;
public:
	virtual ~IFactory() {};
	virtual Component* createInstance(const tinyxml2::XMLElement&) = 0;
};

typedef std::unordered_map<std::string, IFactory*> ComponentFactoryList;

class HealthFactory : public IFactory {
public:
	HealthFactory(LevelManager* levelmanager) { lm = levelmanager; };
	Health* createInstance(const tinyxml2::XMLElement&);
};

class PositionFactory : public IFactory {
public:
	Position* createInstance(const tinyxml2::XMLElement&);
};

class SpriteFactory : public IFactory {
public:
	Sprite* createInstance(const tinyxml2::XMLElement&);
};

class RendererFactory : public IFactory {
public:
	RendererFactory(LevelManager* levelmanager) { lm = levelmanager; };
	Renderer* createInstance(const tinyxml2::XMLElement&);
};

class KeyboardControlFactory : public IFactory {
public:
	KeyboardControlFactory(LevelManager* levelmanager) { lm = levelmanager; };
	KeyboardControl* createInstance(const tinyxml2::XMLElement&);
};

class VelocityFactory : public IFactory {
public:
	Velocity* createInstance(const tinyxml2::XMLElement&);
};

class CollisionFactory : public IFactory {
public:
	CollisionFactory(LevelManager* levelmanager) { lm = levelmanager; };
	Collision* createInstance(const tinyxml2::XMLElement&);
};