#include "Player.h"

#include "Utils.h"
#include <iostream>

Player::Player(const char* name, const char* description, Room* room)
	: Creature(name, description, room)
{
	type = T_Player;
}

void Player::Look(const vector<string>& args) const
{
	if (args.size() == 1)
	{
		parent->Look();
	}
	else
	{
		if (IsEquals(args[1], "me"))
		{
			Creature::Look(args);
			cout << "I think I must save the world, no lose the time looking yourself \n";

		}
	}
}

bool Player::Go(const vector<string>& args)
{
	//Not Yet Implemented
	return true;
}

bool Player::Take(const vector<string>& args)
{
	//Not Yet Implemented
	return true;
}

bool Player::Drop(const vector<string>& args)
{
	//Not Yet Implemented
	return true;
}

void Player::Inventory() const
{
	//Not Yet Implemented

}