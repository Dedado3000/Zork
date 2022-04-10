#include "Exit.h"
#include "Room.h"
#include <iostream>


Exit::Exit(const char* name, const char* description, Room* origin, Room* destination, Direction direction, Direction directionDestination)
	: Entity(name, description, (Entity*)origin),
	locked(false), key(NULL), destination(destination), direction(direction), directionDestination(directionDestination)
{
	type = T_Exit;
	destination->contain.push_back(this);
}

void Exit::Look() const
{
	cout << "a conection from " << parent->name << " to " << ((Entity*)destination)->name << "\n";
	cout << description << "\n";

}

const string Exit::GetDirectionFrom(const Room* room) const
{
	string strReturn = "";
	if ((Entity*)room == parent)
		strReturn = ConvertDirection(direction);
	if (room == destination)
		strReturn = ConvertDirection(directionDestination);

	return strReturn;
}

Room* Exit::GetDestinationFrom(const Room* room) const
{
	if ((Entity*)room == parent)
		return destination;
	if (room == destination)
		return (Room*)parent;

	return NULL;
}


/*
* ConvertDirection()
* Convert direction into a string for reading purpouses
* Input:
	Direction dir <- direction in enum format
  Output:
	string <- direction in string format
*/
const string Exit::ConvertDirection(Direction dir) const
{
	string str = "";
	switch (dir)
	{
		case 0: str = "North";
			break;
		case 1: str = "East";
			break;
		case 2: str = "South";
			break;
		case 4: str = "West";
			break;
		default:
			break;
	}
	return str;
}
