#include "pch.h"
#include "System.h"
#include "Components.h"

bool System::addComponent(Component* comp) {
	subscribers.push_back(comp);
	comp->subscribed = this;
	return true;
}

bool System::removeComponent(Component* comp) {
	std::vector<Component*>::iterator it;
	for (it = subscribers.begin(); it != subscribers.end(); it++) {
		if ((*it)->UID == comp->UID) {
			it = subscribers.erase(it);
			return true;
		}
	}
	return false;
}