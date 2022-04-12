#pragma once
#include "Creature.h"

using namespace std;

class Player :
	public Creature
{
public:
	Player(const char* name, const char* description, Room* room);
	~Player() {};

	void update() {};
	/* HELPERS */
	void Inventory() const;

	/* ACTIONS */
	bool Go(const vector<string>& args);
	void Look(const vector<string>& args) const;
	bool Take(const vector<string>& args);
	bool Drop(const vector<string>& args);
	bool Open(const vector<string>& args);
	bool Close(const vector<string>& args);
};

