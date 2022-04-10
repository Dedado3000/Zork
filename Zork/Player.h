#pragma once
#include "Creature.h"

using namespace std;

class Player :
	public Creature
{
public:
	Player(const char* name, const char* description, Room* room);
	~Player() {};

	/* HELPERS */
	virtual void Inventory() const;

	/* ACTIONS */
	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual bool Open(const vector<string>& args);
	virtual bool Close(const vector<string>& args);
};

