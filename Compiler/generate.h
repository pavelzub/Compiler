#pragma once
#include <map>
#include <vector>
#define initial_state 100

using namespace std;

enum TockenType {
	TK_EOF, TK_BEGIN, TK_STR, TK_DO, TK_ELSE, TK_END, TK_FOR, TK_FUNCTION, TK_IF, TK_FORWARD, TK_UNKNOWN,
	TK_INT, TK_HEX, TK_KEYWORD, TK_ARRAY, TK_OF, TK_PROCEDURE, TK_PROGRAM, TK_RECORD, TK_THEN, TK_TO, TK_TYPE,
	TK_SEP, TK_UNOP, TK_BINOP, TK_COMENT, TK_CODE, TK_REAL, TK_EREAL, TK_OP, TK_IDENT, TK_CHAR, TK_ERROR,
	TK_VAR, TK_WHILE, TK_BREAK, TK_CONTINUE, TK_DOWNTO, TK_EXIT, TK_REPEAT, TK_UNTIL, TK_MOD, TK_NOT, TK_OR,
	TK_XOR, TK_ADD, TK_SUB, TK_AND, TK_DIV, TK_MUL, TK_DIVISION, TK_DEGREE, TK_ADDR, TK_SUBR, TK_MULR, TK_DIVISIONR,
	TK_LESS, TK_MORE, TK_LESSR, TK_MORER, TK_ASSIG, TK_DOG, TK_POINT, TK_COMMA, TK_LSQBR, TK_RSQBR,
	TK_SEMICOLON, TK_COLON, TK_POINTPOINT, TK_LROBR, TK_RROBR, TK_SHR, TK_SHL, TK_UNEQUAL, TK_EQUAL
};


struct Token {
	TockenType type;
	string value;
	string description();
	int col, row;
};

extern map<int, pair<TockenType, int>> final_states;
extern map<int, vector<int>> transition_table;

int chartostate(char c);