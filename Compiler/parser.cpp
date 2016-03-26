#include "parser.h"
#define maxlvl 9

map<TockenType, int> priority_table = { {TK_LROBR, 1}, {TK_RROBR, 1}, {TK_LSQBR, 1}, {TK_RSQBR, 1}, {TK_POINT, 1},
{TK_MOD, 2}, {TK_DIV, 2}, {TK_MUL, 2}, {TK_DIVISION, 2},
{TK_ADD, 3}, {TK_SUB, 3},
{TK_SHL, 4}, {TK_SHR, 4},
{TK_MORE, 5}, {TK_LESS, 5}, {TK_MORER, 5}, {TK_LESSR, 5}, {TK_EQUAL, 5}, {TK_UNEQUAL, 5},
{TK_AND, 6}, {TK_OR, 7},
{TK_ASSIG, 8}, {TK_DIVISIONR, 8}, {TK_ADDR, 8}, {TK_SUBR, 8}, {TK_MULR, 8},
{TK_COMMA, 9}};


void ParseExp::Print() {
	Top->print(0);
};

vector<Node*> ParseExp::ParseArr() {
	return {nullptr};
};

vector<Node*> ParseExp::ParseFunc() {
	return {nullptr};
};

Node* ParseExp::ParseUnOp() {
	Token tk = scaner.Get();
	scaner.Next();
	return new UnOpNode(tk, ParseFactor());
};

Node* ParseExp::ParseStruct() {
	scaner.Next();
	return ParseFactor();
};

Node* ParseExp::ParseFactor() {
	Node* root = nullptr;
	switch (scaner.Get().type)
	{
	case TK_IDENT: case TK_INT: case TK_REAL: {
		root = new ConstNode(scaner.Get());
		break;
	}
	case TK_RROBR: case TK_SEMICOLON: return nullptr;
	case TK_LROBR: {
		scaner.Next();
		root = ParseExpr(maxlvl);
		if (scaner.Get().type != TK_RROBR) throw CompileException("Expected closing bracket", scaner.Get());
		break;
	}
	case TK_ADD: case TK_SUB: return ParseUnOp();
	default:
		throw CompileException("Wrong expression", scaner.Get());
	}
	scaner.Next();
	return root;
};

Node* ParseExp::ParseExpr(int lvl) {
	if (!lvl) return ParseFactor();
	Node *left = nullptr;
	left = ParseExpr(lvl - 1);
	if (lvl == 1) {
		Token tk = scaner.Get();
		switch (tk.type){
		case TK_LROBR: return new FunctionalNode(tk, left, ParseFunc());
		case TK_LSQBR: return new ArrNode(tk, left, ParseArr());
		case TK_POINT: return new StructNode(tk, left, ParseStruct());
		default:
			break;
		}
	}
	else {
		while (priority_table[scaner.Get().type] == lvl) {
			Token tk = scaner.Get();
			scaner.Next();
			left = new BinOpNode(tk, left, ParseExpr(lvl - 1));
		}
	}
	return left;
};

void ParseExp::Parse() {
	scaner.Next();
	Top = ParseExpr(maxlvl);
};
