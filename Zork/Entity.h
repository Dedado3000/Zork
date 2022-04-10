#pragma once

#include <string>
#include <list>

using namespace std;

enum Type
{
	T_Creature,
	T_Exit,
	T_Room,
	T_Item,
	T_Player
};

class Entity
{

public:
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity() {};

	virtual void Update() {};

	//Helpers
	void ChangeParent(Entity* parent);

	//Actions
	virtual void Look()const;

public:
	Type type;
	string name;
	string description;

	Entity* parent;
	list<Entity*> contain;
};

