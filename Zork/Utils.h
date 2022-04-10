#pragma once

#include <string>
#include <vector>

using namespace std;

enum Direction;

void Tokenize(const string& line, vector<string>& args);

bool IsEquals(const string& a, const char* b);


Direction ConvertString(string strdir);
