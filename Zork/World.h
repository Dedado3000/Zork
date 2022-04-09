#pragma once

#include <string>
#include <list>
#include <vector>
#include <time.h>


using namespace std;



class Entity;

class World
{
public:
	World();
	~World();

	bool PerformAction(vector<string>& args);
	bool ConvertAction(vector<string>& args);
	void UpdateGame();

private:

	list<Entity*> entities;
	Entity* player;
};

