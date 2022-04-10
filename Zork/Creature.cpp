#include "Creature.h"


Creature::Creature(const char* title, const char* description, Room* room) :
	Entity(title, description, (Entity*)room)
{	
	type = T_Creature;
	Location = room;
}


void Creature::Look(const vector<string>& args) const
{
	Entity::Look();

}


bool Creature::Go(const vector<string>& args)
{
	//Not Yet Implemented
	return true;
}

bool Creature::Take(const vector<string>& args)
{
	//Not Yet Implemented
	return true;
}

bool Creature::Drop(const vector<string>& args) 
{
	//Not Yet Implemented
	return true;
}

void Creature::Inventory() const
{
	//Not Yet Implemented

}