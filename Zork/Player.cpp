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
	//Look the room
	if (args.size() == 1)
	{
		parent->Look();
	}
	//Look Yourself/A path/An Item in the room or your inventory//NPC
	else if (args.size() == 2)
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
		else
		{
			for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
			{
				if ((*it)->type == T_Item)
				{
					Item* item = (Item*)*it;
					if (item->name.compare(args[1]) == 0)
					{
						item->Look();
						return;
					}
				}

				if ((*it)->type == T_NPC || (*it)->type == T_Creature)
				{
					Creature* creature = (Creature*)*it;
					if (creature->name.compare(args[1]) == 0)
					{
						creature->Look(args);
						return;
					}
				}
			}

			for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it)
			{
				if ((*it)->type == T_Item)
				{
					Item* item = (Item*)*it;
					if (item->name.compare(args[1]) == 0)
					{
						item->Look();
						return;
					}
				}
			}

			cout << "> I don't see anything to look that is called " << args[1] << "\n";
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
			cout << "The "<<exit->name << " is locked try to open it with a key\n";
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
	//Take an item in the street
	if (args.size() == 2)
	{
		for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
		{
			if ((*it)->type == T_Item)
			{
				Item* item = (Item*)*it;
				if (args[1].compare(item->name) == 0)
				{
					if (item->itemType == I_Container)
					{
						cout << "-|- You can't pick this\n";
						return true;
					}
					item->ChangeParent((Entity*)this);
					cout << "-|- You picked " << item->name << "\n";
					return true;
				}
			}
		}
	}
	else if (args.size() == 3)
	{
		//Search for an item with the name of the container
		for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
		{
			if ((*it)->type == T_Item && args[1].compare((*it)->name) == 0)
			{
				
				for (list<Entity*>::const_iterator it2 = (*it)->contain.begin(); it2 != (*it)->contain.cend(); ++it2)
				{
					if ((*it2)->type == T_Item && args[2].compare((*it2)->name) == 0)
					{
						cout << "-|- You picked " << (*it2)->name  << " from " << (*it)->name << "\n";
						(*it2)->ChangeParent((Entity*)this);
						return true;
					}
				}
				
			}

		}


	}

	cout << "-|- There is nothing to pick with that name\n";
	return true;
}

bool Player::Drop(const vector<string>& args)
{
	if (args.size() == 2)
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
	}
	else if (args.size() == 3) 
	{
		for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it)
		{
			if (args[2].compare((*it)->name) == 0)
			{
				//Search the item to drop
				for (list<Entity*>::const_iterator it2 = parent->contain.begin(); it2 != parent->contain.cend(); ++it2)
				{
					if ((*it2)->type == T_Item && args[1].compare((*it2)->name) == 0)
					{
						cout << "-|- You droped " << (*it)->name << " inside " << (*it2)->name << "\n";
						(*it)->ChangeParent((*it2));
						return true;
					}
				}
				cout << "-|- There is nothing where to drop with that name\n";
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


bool Player::Open(const vector<string>& args)
{
	for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
	{
		if ((*it)->type == T_Exit)
		{
			Exit* ex = (Exit*)*it;
			if (ex->key != NULL && args[1].compare(ex->name) == 0)
			{
				if (args[2].compare(ex->key->name)==0)
				{
					for (list<Entity*>::const_iterator it2 = contain.begin(); it2 != contain.cend(); ++it2)
					{
						if (*it2 == ex->key)
						{
							ex->locked = false;
							cout << "-|- You feel a click and " << ex->name << " opened with " << args[2] << "\n";
							return true;
						}
					}
					cout << "-|- I dont have " << args[2] << " in my inventory\n";
					return true;
				}
				else
				{
					for (list<Entity*>::const_iterator it2 = contain.begin(); it2 != contain.cend(); ++it2)
					{
						if (args[2].compare((*it2)->name) == 0)
						{
							cout << "-|- I can't Open " << ex->name << " with " << args[2] << "\n";
							return true;
						}
					}
					cout << "-|- I dont have "<< args[2] << " in my inventory\n";
					return true;

				}
			}
		}
	}
	cout << "-|- There is no Path with the name "<< args[1] <<"\n";
	return true;
}

bool Player::Close(const vector<string>& args)
{
	for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
	{
		if ((*it)->type == T_Exit)
		{
			Exit* ex = (Exit*)*it;
			if (ex->key != NULL && args[1].compare(ex->name) == 0)
			{
				if (args[2].compare(ex->key->name) == 0)
				{
					for (list<Entity*>::const_iterator it2 = contain.begin(); it2 != contain.cend(); ++it2)
					{
						if (*it2 == ex->key)
						{
							ex->locked = true;
							cout << "-|- You feel a click and " << ex->name << " closed with " << args[2] << "\n";
							return true;
						}
					}
					cout << "-|- I dont have " << args[2] << " in my inventory\n";
					return true;
				}
				else
				{
					for (list<Entity*>::const_iterator it2 = contain.begin(); it2 != contain.cend(); ++it2)
					{
						if (args[2].compare((*it2)->name) == 0)
						{
							cout << "-|- I can't Close " << ex->name << " with " << args[2] << "\n";
							return true;
						}
					}
					cout << "-|- I dont have " << args[2] << " in my inventory\n";
					return true;

				}
			}
		}
	}
	cout << "-|- There is no Path with the name " << args[1] << "\n";
	return true;
}