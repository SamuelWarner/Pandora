#include "pch.h"
#include "ControlSystem.h"


ControlSystem::ControlSystem()
{
}


ControlSystem::~ControlSystem()
{
}

void ControlSystem::update(){
	for (size_t i = 0, lenght = subscribers.size(); i < lenght; ++i) {
		subscribers[i]->update();
	}
}
