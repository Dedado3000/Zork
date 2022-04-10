#include "Room.h"

#include "Exit.h"
#include "Item.h"
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
			cout << "- to the " << ex->GetDirectionFrom(this) << " you can see a "<< ex->name << " to go to the " << ex->GetDestinationFrom(this)->name << "\n";
		}
	}
	/* ITEMS*/
	for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it)
	{
		if ((*it)->type == T_Item)
		{
			Item* item = (Item*)*it;
			cout << "\n- In the floor you can see a " << item->name << "\n";
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