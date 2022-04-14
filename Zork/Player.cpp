#include "Player.h"
#include "Exit.h"
#include "Item.h"
#include "NPC.h"
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
			cout << "> I think I must save the world, not losing the time looking myself \n";

		}
		else if (ConvertString(args[1]) != D_Novalid)
		{
			bool found = false;
			Exit* exit = ((Room*)parent)->GetExit(ConvertString(args[1]));
			/*for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
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
			}*/
			if (exit != NULL)
			{
				exit->Look();
			}
			else
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

		cout << "\nYou go From your position to " << exit->GetDestinationFrom((Room*)parent)->name << "...\n" << "When you arrive you take a look...";
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


/*
* Talk()
* Receive the input from a NPC
* Input:
	vector<string>& args <- Instructions to talk
  Output:
	bool <- The action can be performed
  Console Output:
	The action you made if its posible
*/
bool Player::Talk(const vector<string>& args)
{


	for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
	{
		if ((*it)->type == T_NPC)
		{
			NPC* npc = (NPC*)*it;
			if (npc->name.compare(args[1]) == 0)
			{
				if (!npc->completedQuest)
				{
					cout << "\n - " << npc->name << ":" << npc->talkQuest << ".\n";
				}
				else
				{
					cout << "\n - " << npc->name << ":" << npc->talkEndedQuest << ".\n";
				}
				return true;
			}
		}
	}

	cout << "\nThere is nobody to talk named " << args[1] << ".\n";

	return true;
}


/*
* Talk()
* Receive the input from a NPC
* Input:
	vector<string>& args <- Instructions to go
  Output:
	bool <- The action can be performed
  Console Output:
	The action you made if its posible
*/
bool Player::Give(const vector<string>& args)
{

	NPC* npc = NULL;
	for (list<Entity*>::const_iterator it = parent->contain.begin(); it != parent->contain.cend(); ++it)
	{
		if ((*it)->type == T_NPC)
		{
			npc = (NPC*)*it;
			if (npc->name.compare(args[1]) == 0)
			{
				if (npc->completedQuest)
				{
					cout << "\n - " << npc->name << ": Boy, You give my "<< npc->wanted->name <<" a second ago.\n";
					return true;
				}
			}
		}
	}

	if (npc != NULL)
	{

		for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it)
		{
			if ((*it)->type == T_Item)
			{
				Item* item = (Item*)*it;
				if (item->name.compare(args[2]) == 0)
				{
					if (item == npc->wanted)
					{
						cout << "\n - " << npc->name << ": "<< npc->talkEndedQuest <<".\n";
						npc->completedQuest = true;
						item->ChangeParent(npc);
						return true;
					}
					cout << "\n - " << npc->name << ": I don't want this.\n";
					return true;

				}
			}
		}
	}
	else
	{
		cout << "\nThere is nobody to give the item named " << args[1] << ".\n";
	}

	cout << "\n#Error404 Item not Found .\n";


	return true;
}