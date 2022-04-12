#include "NPC.h"


NPC::NPC(const char* name, const char* description, Room* room, Item* wanted, const char* quest, const char* completed)
	: Creature(name, description, room),
	wanted(wanted), completedQuest(false), talkQuest(quest), talkEndedQuest(completed)
{
	type = T_NPC;
}


void NPC::Look(const vector<string>& args) const
{
	Creature::Look(args);

}