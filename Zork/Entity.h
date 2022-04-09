#pragma once

#include <string>
#include <list>

using namespace std;

enum Type
{
	Creature,
	Exit,
	Room,
	Item
};

class Entity
{
private:
	Type type;
	string name;
	string description;

	Entity* parent;
	list<Entity*> contain;

public:
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();

	virtual void Update();
	virtual void Look();


};

