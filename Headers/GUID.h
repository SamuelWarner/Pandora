#pragma once
#include <vector>

class GUID
{
	static int id;
	static std::vector<int> idPool;
public:
	GUID();
	~GUID();
	static int getID();
	static void returnID(int);
};

