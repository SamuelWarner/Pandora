#pragma once
#include <vector>
class Component;

class System
{
protected:
	std::vector<Component*> subscribers;
public:
	System() {};
	virtual ~System() {};
	bool addComponent(Component*);
	bool removeComponent(Component*);
};

