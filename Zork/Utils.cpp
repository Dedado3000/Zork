#include "Utils.h"


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