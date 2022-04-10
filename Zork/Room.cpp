#include "Room.h"

#include "Exit.h"
#include "Utils.h"
#include <iostream>


Room::Room(const char* name, const char* description)
	: Entity(name, description, NULL)
{
	type = T_Room;
}


/*
* Look()
* Describe the Room apeareance
  Console Output:
	All the things at the room
*/
void Room::Look() const
{
	Entity::Look();

	/* EXITS*/
	for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it)
	{
		if ((*it)->type == T_Exit)
		{
			Exit* ex = (Exit*)*it;
			cout << "\nto the " << ex->GetDirectionFrom(this) << " you can see " << ex->GetDestinationFrom(this)->name << "\n";
		}
	}

}


/*
* GetExit()
* Get the exit from a direction
* Input:
	Direction direction <- Where the players want to go
  Output:
	Exit <- Exit the player must take to go
*/
Exit* Room::GetExit(Direction direction) const
{
	for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it)
	{
		if ((*it)->type == T_Exit)
		{
			Exit* ex = (Exit*)*it;
			if (ConvertString(ex->GetDirectionFrom(this)) == direction)
				return ex;
		}
	}

	return NULL;
}