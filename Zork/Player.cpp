#include "Player.h"
#include "Exit.h"
#include "Item.h"
#include "Room.h"
#include "Utils.h"
#include <iostream>

Player::Player(const char* name, const char* description, Room* room)
	: Creature(name, description, room)
{
	type = T_Player;
}


/*
* Look()
* Tell the description of what you indicate in the instruction
* Input:
	vector<string>& args <- Instructions to look
  Console Output:
	The description of the entity you look
*/
void Player::Look(const vector<string>& args) const
{
	if (args.size() == 1)
	{
		parent->Look();
	}
	else
	{
		if (IsEquals(args[1], "me"))
		{
			Creature::Look(args);
			cout << "> I think I must save the world, no lose the time looking myself \n";

		}
		else if (ConvertString(args[1]) != D_Novalid)
		{
			bool found = false;
			for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
			{
				if ((*it)->type == T_Exit)
				{
					Exit* ex = (Exit*)*it;
					if (ex->direction == ConvertString(args[1]))
					{
						ex->Look();
						found = true;
					}
				}
			}
			if (!found)
				cout << "> I don't see any Path in the " << args[1] << "\n";
		}


	}
}

/*
* Go()
* Change the location of the player
* Input:
	vector<string>& args <- Instructions to go
  Output:
	bool <- The action can be performed
  Console Output:
	The action you made if its posible
*/
bool Player::Go(const vector<string>& args)
{
	Direction dir = ConvertString(args[1]);
	Exit* exit = ((Room*)parent)->GetExit(dir);

	if (exit != NULL)
	{
		if (exit->locked == true)
		{
			cout << "The door is locked try to open it with a key\n";
			return true;
		}

		cout << "\nYou go From your position to " << exit->GetDestinationFrom((Room*)parent)->name << "...\n" << "When you arrive you";
		ChangeParent(exit->GetDestinationFrom((Room*)parent));
		parent->Look();
		return true;
	}

	cout << "\nYou can't find a path at " << args[1] << ".\n";

	return true;
}

bool Player::Take(const vector<string>& args)
{

	for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
	{
		if ((*it)->type == T_Item)
		{
			Item* item = (Item*)*it;
			if (args[1].compare(item->name) == 0)
			{
				item->ChangeParent((Entity*)this);
				cout << "-|- You picked " << item->name << "\n";
				return true;
			}
		}
	}
	cout << "-|- There is nothing to pick with that name\n";

	return true;
}

bool Player::Drop(const vector<string>& args)
{

	for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it)
	{
		if ((*it)->type == T_Item)
		{
			Item* item = (Item*)*it;
			if (args[1].compare(item->name) == 0)
			{
				item->ChangeParent(this->parent);
				cout << "-|- You droped " << item->name << "\n";
				return true;
			}
		}
	}
	cout << "-|- There is nothing to drop with that name\n";
	return true;
}

void Player::Inventory() const
{
	cout << "> You open your bag\n";
	for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it) 
	{
		if ((*it)->type == T_Item)
		{
			Item* item = (Item*)*it;
			item->Look();
		}
	}
	cout << "> You close your bag\n";
	
	//Not Yet Implemented

}