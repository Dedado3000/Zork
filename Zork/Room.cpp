#include "Room.h"

#include <iostream>


Room::Room(const char* name, const char* description)
	: Entity(name, description, NULL)
{
	type = T_Room;
}

void Room::Look() const
{
	Entity::Look();
	//cout << "\n" << name << "\n" << description << "\n";

}

Exit* Room::GetExit(const string& direction) const
{
	//Not implemented Yet

	return NULL;
}