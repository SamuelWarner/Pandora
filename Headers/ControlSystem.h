#pragma once
#include "Components.h"
#include <vector>
#include "System.h"

class ControlSystem : public System
{
public:
	ControlSystem();
	~ControlSystem();
	void update();
};

