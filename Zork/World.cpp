#include "World.h"

#include "Entity.h"
#include "Creature.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Utils.h"
#include <iostream>



World::World()
{
	/* ROOMS */
	Room* Facade = new Room("Facade", "You are in front of a big white house.");
	Room* Street = new Room("Street", "Its an old route with no movement.");

	entities.push_back(Facade);
	entities.push_back(Street);

	/* CONECTIONS*/
	Exit* exit1 = new Exit("Path", "An old path who lived better times", Facade, Street, D_South, D_North);

	entities.push_back(exit1);

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
		else
			canConvert = false;

		break;
	case 2:
		if (IsEquals(args[0], "look"))
			player->Look(args);
		else if (IsEquals(args[0], "go"))
			player->Go(args);
		else
			canConvert = false;

		break;
	default:
		canConvert = false;
	}


	return canConvert;
}
