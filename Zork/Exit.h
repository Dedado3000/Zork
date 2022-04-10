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
	D_West,
	D_Novalid
};

class Exit :
	public Entity
{
public:
	Exit(const char* name, const char* description, Room* origin, Room* destination, Direction direction, Direction directionDestination);
	~Exit() {};

	void update() {};

	void Look() const;

	const string GetDirectionFrom(const Room* room) const;
	Room* GetDestinationFrom(const Room* room) const;

	/* CONVERTERS */
	const string ConvertDirection(Direction dir) const;
	//const Direction ConvertString(string dir) const;


public:
	bool locked;
	Direction direction,directionDestination;
	Room* destination;
	Entity* key;
};

