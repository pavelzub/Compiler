#pragma once
#include "generate.h"
#include <iostream>
#include <string>


using namespace std;

class CompileException {
private:
	int row, col;
	string massage;

public:
	CompileException(string m, int l, int c) : row(l), col(c), massage(m) {}
	CompileException(string m, Token token) : row(token.row), col(token.col), massage(m) {}
	CompileException(string m) : col(-1), row(-1), massage(m) {}

	void print() const;
};
