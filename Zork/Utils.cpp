#include "Utils.h"
#include "Exit.h"

/*
* Tokenize()
* Convert player input into a diferent arguments
* Input:
	string& line <- String with action ej "open door"
	vector<strign>& args <- Container for the action
*/
void Tokenize(const string& line, vector<string>& args)
{
	const char* str = line.c_str();

	do
	{
		const char* begin = str;

		while (*str != ' ' && *str)
			str++;

		args.push_back(string(begin, str));
	} while (0 != *str++);
}


bool IsEquals(const string& a, const char* b)
{
	return _stricmp(a.c_str(), b) == 0;
}

bool IsEquals(const string& a, string* b)
{
	return _stricmp(a.c_str(), b->c_str()) == 0;
}

/*
* ConvertString()
* Change a string to a direction
* Input:
	string strdir <- the direction in string format
  Output:
	Direction <- The direction transformed into an enum
*/
Direction ConvertString(string strdir)
{
	Direction dir = D_Novalid;
	if (strdir.compare("North") == 0 || strdir.compare("north") == 0 || strdir.compare("n") == 0)
		dir = D_North;
	else if (strdir.compare("South") == 0 || strdir.compare("south") == 0 || strdir.compare("s") == 0)
		dir = D_South;
	else if (strdir.compare("West") == 0 ||  strdir.compare("west") == 0 || strdir.compare("w") == 0)
		dir = D_West;
	else if (strdir.compare("East") == 0 || strdir.compare("east") == 0 || strdir.compare("e") == 0)
		dir = D_East;

	return dir;
}