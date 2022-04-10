#include "Entity.h"

#include <iostream>

Entity::Entity(const char* name, const char* description, Entity* parent = NULL) :
	name(name), description(description), parent(parent)
{
	if (parent != NULL)
		parent->contain.push_back(this);
}

/* HELPERS */

void Entity::ChangeParent(Entity* parent_to_change)
{

	if (parent != NULL)
		parent->contain.remove(this);

	parent = parent_to_change;

	if (parent != NULL)
		parent->contain.push_back(this);
}

/* ACTIONS */
void Entity::Look() const
{
	cout << "\n" << name << "\n" << description << "\n";
}