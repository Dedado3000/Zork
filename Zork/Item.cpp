#include "Item.h"
#include "Utils.h"


#include <iostream>

Item::Item(const char* name, const char* description, Entity* parent, ItemT itemtype, const char* help)
	:Entity(name, description, parent)
{
	type = T_Item;
	helpString = help;
}

void Item::Look() const
{
	Entity::Look();
	if (helpString.compare("") != 0)
		cout << helpString << "\n";
	
}