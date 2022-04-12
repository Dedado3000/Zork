#pragma once
#include "Creature.h"
#include <string>


using namespace std;

class Item;

class NPC :
	public Creature
{
public:
	NPC(const char* name, const char* description, Room* room, Item* wanted, const char* quest, const char* congrats);
	~NPC() {};

	void update() {};


	/* ACTIONS */
	bool Go(const vector<string>& args) { return true; };
	void Look(const vector<string>& args) const;
	bool Take(const vector<string>& args) { return true; };
	bool Drop(const vector<string>& args) { return true; };
	bool Open(const vector<string>& args) { return true; };
	bool Close(const vector<string>& args) { return true; };

	Item* wanted;
	bool completedQuest;
	string talkQuest;
	string talkEndedQuest;
};

