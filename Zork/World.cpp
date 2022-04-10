#include "World.h"

#include "Entity.h"
#include "Creature.h"
#include "Player.h"
#include "Room.h"
#include "Utils.h"
#include <iostream>



World::World()
{
	/* ROOMS */
	Room* Facade = new Room("Facade", "You are in front of a big white house.");

	entities.push_back(Facade);

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
		else
			canConvert = false;

		break;
	default:
		canConvert = false;
	}


	return canConvert;
}
