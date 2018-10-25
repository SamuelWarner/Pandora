#pragma once
#include "Components.h"
#include "System.h"

class LifeSystem : public System
{
public:
	LifeSystem();
	~LifeSystem();
	void update();
};

