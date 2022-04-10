#include "World.h"

#include "Entity.h"
#include "Creature.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Utils.h"
#include "Item.h"
#include <iostream>



World::World()
{
	/* ROOMS */
	Room* Facade = new Room("Facade", "You are in front of a big white house.");
	Room* Street = new Room("Street", "Its an old route with no movement.");
	Room* House = new Room("House", "It seems less wide when you are inside.");

	entities.push_back(Facade);
	entities.push_back(Street);
	entities.push_back(House);
	/* CONECTIONS*/
	Exit* exit1 = new Exit("Path", "An old path who lived better times", Facade, Street, D_South, D_North);
	Exit* exit2 = new Exit("Door", "An old who seems locked", Facade, House, D_West, D_East);

	exit2->locked = true;

	entities.push_back(exit1);
	entities.push_back(exit2);

	/* ITEMS*/

	Item* item1 = new Item("Trash", "A typical big trash who seem empty", House, I_Container, "Maybe there is something inside");
	Item* item2 = new Item("Letter", "A letter with typical congrats text, try to look", item1, I_Common, "Thank you for playing my game, you can exit typing 'exit' or 'quit'");

	entities.push_back(item1);
	entities.push_back(item2);

	Item* key = new Item("Key", "A pinky key with the phrase 'dear house'", Street, I_Key, "Maybe this can help me opening some door");

	exit2->key = key;
	entities.push_back(key);


	/* PLAYER */
	player = new Player("Yourself", "You look so bad, please get a shower soon",Facade);

	entities.push_back(player);
}


World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete* it;

	entities.clear();
}

bool World::PerformAction(vector<string>& args)
{
	bool performed = true;

	if (args.size() > 0 && args[0].length() > 0)
		performed = ConvertAction(args);

	if (performed)
	{
		UpdateGame();
	}

	return performed;
}

void World::UpdateGame()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		(*it)->Update();

}


/*
* ConvertAction()
* Convert player action into the world actionm
* Input:
	vector<string>& args <- Instructions to do
  Output:
	bool <- The action can be performed or not
*/
bool World::ConvertAction(vector<string>& args)
{
	bool canConvert = true;
	switch (args.size())
	{
	case 1:
		if (IsEquals(args[0], "look"))
			player->Look(args);
		else if (IsEquals(args[0], "inventory") || IsEquals(args[0], "bag"))
			player->Inventory();
		else if (IsEquals(args[0], "go"))
			cout << "Go where?\n";
		else
			canConvert = false;
		break;
	case 2:
		if (IsEquals(args[0], "look"))
			player->Look(args);
		else if (IsEquals(args[0], "go"))
			player->Go(args);
		else if (IsEquals(args[0], "pick") || IsEquals(args[0], "take") )
			player->Take(args);
		else if (IsEquals(args[0], "drop"))
			player->Drop(args);
		else if (IsEquals(args[0], "inventory") || IsEquals(args[0], "bag"))
			player->Inventory();
		else if (IsEquals(args[0], "open") || IsEquals(args[0], "close") )
			cout << "You need a item to use as key\n";
		else
			canConvert = false;
		break;
	case 3:
		if (IsEquals(args[0], "open"))
			player->Open(args);
		else if (IsEquals(args[0], "close"))
			player->Close(args);
		else if (IsEquals(args[0], "pick") || IsEquals(args[0], "take"))
			player->Take(args);
		else if (IsEquals(args[0], "drop"))
			player->Drop(args);
		else
			canConvert = false;
		break;
	default:
		canConvert = false;
	}


	return canConvert;
}
