#include "Item.h"
#include "Utils.h"


#include <iostream>

Item::Item(const char* name, const char* description, Entity* parent, ItemT itemtype, const char* help)
	:Entity(name, description, parent)
{
	type = T_Item;
	itemType = itemtype;
	helpString = help;
}

void Item::Look() const
{
	Entity::Look();
	if (helpString.compare("") != 0)
		cout << helpString << "\n";
	if (itemType == I_Container)
	{
		cout << "You start looking inside the " << name << "\n";
		for (list<Entity*>::const_iterator it = contain.begin(); it != contain.cend(); ++it)
		{
			cout << "- You find a " << (*it)->name << "\n";
		}

		cout << "\nThere is nothing left in the " << name << "\n";
	}
}