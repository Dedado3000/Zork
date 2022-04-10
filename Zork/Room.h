#pragma once
#include "Entity.h"

#include <string>
#include <list>

class Exit;

using namespace std;

class Room :
	public Entity
{
public:

	Room(const char* name, const char* description);
	~Room() {};

	void Look() const;

	Exit* GetExit(const string& direction) const;

};

