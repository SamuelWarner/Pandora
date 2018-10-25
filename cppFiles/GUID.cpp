#include "pch.h"
#include "GUID.h"

int GUID::id = 0;
std::vector<int> GUID::idPool;

GUID::GUID()
{
}


GUID::~GUID()
{
}

int GUID::getID() {
	if (idPool.empty()) {
		return id++;
	}
	else {
		int ID = idPool.back();
		idPool.pop_back();
		return ID;
	}
}

void GUID::returnID(int ID) {
	idPool.push_back(ID);
}