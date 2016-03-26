#pragma once
#include "leckser.h"
#include "Node.h"

class ParseExp {
	Tokenizer scaner;
	Node *Top;
	Node* ParseExpr(int lvl);
	Node* ParseFactor();
	vector<Node*> ParseFunc();
	vector<Node*> ParseArr();
	Node* ParseStruct();
	Node* ParseUnOp();
public:
	void Parse();
	void Print();
	ParseExp(Tokenizer tk) : scaner(tk) {};
};


