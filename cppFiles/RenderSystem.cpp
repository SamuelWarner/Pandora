#include "pch.h"
#include "RenderSystem.h"


RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::update() {
	for (size_t i = 0, lenght = subscribers.size(); i < lenght; ++i) {
		subscribers[i]->update();
	}
}