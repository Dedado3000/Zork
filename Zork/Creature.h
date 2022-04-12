#pragma once
#include "Entity.h"

#include <string>
#include <vector>

class Room;
class Item;

using namespace std;


class Creature :
	public Entity
{
public:
	Creature(const char* name, const char* description, Room* room);
	~Creature() {};

	virtual void Update() {};

	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual void Inventory() const;


	Room* GetRoom() const;

public:
	
	Room* Location;

};

