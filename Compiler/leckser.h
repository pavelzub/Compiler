#pragma once
#include "generate.h"
#include "myexception.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class Tokenizer {
	string data;
	int nextcol, nextrow;
	int index;
	void SetTocken(int i, string val);
	void inccol(char c, bool flag);
	Token token;
public:
	Tokenizer(string str);
	Token Next();
	Token Get();
};