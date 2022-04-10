#pragma once

#include <string>
#include "Entity.h"

class Room;

using namespace std;

enum ItemT
{
	I_Common,
	I_Key,
	I_Container
};

class Item :
	public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent, ItemT item_type = I_Common, const char* help = "");
	~Item() {};

	void Look() const;

public:
	ItemT itemType;
	string helpString;
};

