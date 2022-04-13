#include "World.h"

#include "Entity.h"
#include "Creature.h"
#include "Player.h"
#include "NPC.h"
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
	Room* Basement = new Room("Basement", "I can't see anything here.");

	entities.push_back(Facade);
	entities.push_back(Street);
	entities.push_back(House);
	entities.push_back(Basement);
	/* CONECTIONS*/
	Exit* exit1 = new Exit("Path", "An old path who lived better times", Facade, Street, D_South, D_North);
	Exit* exit2 = new Exit("Door", "An old who seems locked", Facade, House, D_West, D_East);
	Exit* exit3 = new Exit("Door", "An old who seems locked", House, Basement, D_Down, D_Up);

	exit2->locked = true;

	entities.push_back(exit1);
	entities.push_back(exit2);
	entities.push_back(exit3);

	/* ITEMS*/

	Item* item1 = new Item("Trash", "A typical big trash who seem empty", Basement, I_Container, "Maybe there is something inside");
	Item* item2 = new Item("Letter", "A letter with typical congrats text, try to look", item1, I_Common, "Thanks, you found the 'easterEgg', this isn't the item that Timmy is searching");
	Item* toy = new Item("Toy", "Timmy Favourite Toy, it's a giant square", item1, I_Common, "Thank you for playing my game, you can exit typing 'exit' or 'quit'");
	Item* mailBox = new Item("Mailbox", "An open mailbox, maybe you can take a look inside ", Facade, I_Container, "");
	Item* mail = new Item("Mail", "Hello, im your friend Timmy, can you take my keys from the street and come to my place", mailBox, I_Common, "");

	entities.push_back(item1);
	entities.push_back(item2);
	entities.push_back(toy);
	entities.push_back(mailBox);
	entities.push_back(mail);

	Item* key = new Item("Key", "A pinky key with the phrase 'dear house'", Street, I_Key, "Maybe this can help me opening some door");

	exit2->key = key;
	entities.push_back(key);

	/* NPC */
	NPC* timmy = new NPC("Timmy", "Your friend from Highschool", House, toy, "I lost my Toy, can you help me and Giving back?", "Thanks for your help, remember you can exit from this simulation typing exit");
	entities.push_back(timmy);



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
		else if (IsEquals(args[0], "talk"))
			player->Talk(args);
		else if (IsEquals(args[0], "open") || IsEquals(args[0], "close") )
			cout << "You need a item to use as key\n";
		else if (IsEquals(args[0], "give"))
			cout << "You need something to give \n";
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
		else if (IsEquals(args[0], "give"))
			player->Give(args);
		else
			canConvert = false;
		break;
	default:
		canConvert = false;
	}


	return canConvert;
}
