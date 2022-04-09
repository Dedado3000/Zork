#include "World.h"

#include "Entity.h"
#include <iostream>



World::World()
{

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



	return canConvert;
}
