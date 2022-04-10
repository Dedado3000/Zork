#pragma once
#include "Entity.h"
#include <string>
class Room;

using namespace std;

enum Direction
{
	D_North,
	D_East,
	D_South,
	D_West
};

class Exit :
	public Entity
{
public:
	Exit(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination);
	~Exit();

	void Look() const;

	const string& GetNameFrom(const Room* room) const;
	Room* GetDestinationFrom(const Room* room) const;

public:
	bool locked;
	Direction direction;
	Room* destination;
	Entity* key;
};

