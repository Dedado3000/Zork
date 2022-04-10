#pragma once

#include <string>
#include <list>
#include <vector>


using namespace std;



class Entity;
class Player;

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
	Player* player;
};

