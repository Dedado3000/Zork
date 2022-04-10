#pragma once
#include "Entity.h"

#include <string>
#include <list>

class Exit;
enum Direction;

using namespace std;

class Room :
	public Entity
{
public:

	Room(const char* name, const char* description);
	~Room() {};
	void update() {};

	void Look() const;

	Exit* GetExit(const Direction direction) const;

};

