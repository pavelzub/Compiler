#include "leckser.h"


vector<string> errors = {"BadNL", "BadEOF", "BadChar", "NoExp", "NoFract", "NoHex", "NoCC", "BadCC"};
map<string, TockenType> keyword = { {"begin", TK_BEGIN}, {"forward", TK_FORWARD}, {"do", TK_DO}, {"else", TK_ELSE},
	{"end", TK_END}, {"for", TK_FOR}, {"function", TK_FUNCTION}, {"if", TK_IF}, {"array", TK_ARRAY}, {"to", TK_TO},
	{"of", TK_OF}, {"procedure", TK_PROCEDURE}, {"program", TK_PROGRAM}, {"record", TK_RECORD}, {"then", TK_THEN},
	{"type", TK_TYPE}, {"var", TK_VAR}, {"while", TK_WHILE}, {"break", TK_BREAK}, {"continue", TK_CONTINUE},
	{"downto", TK_DOWNTO}, {"exit", TK_EXIT}, {"repeat", TK_REPEAT}, {"until", TK_UNTIL}, {"and", TK_AND}, {"div", TK_DIV},
	{"mod", TK_MOD}, {"not", TK_NOT}, {"or", TK_OR}, {"xor", TK_XOR}, {"+", TK_ADD}, {"-", TK_SUB}, {"*", TK_MUL},
	{"/", TK_DIVISION}, {"^", TK_DEGREE}, {"+=", TK_ADDR}, {"-=", TK_SUBR}, {"*+", TK_MULR}, {"/=", TK_DIVISIONR},
	{"<", TK_LESS}, {">", TK_MORE}, {"<=", TK_LESSR}, {">=", TK_MORER}, {"<>", TK_UNEQUAL}, {"=", TK_EQUAL}, {":=", TK_ASSIG},
	{"@", TK_DOG}, {".", TK_POINT}, {",", TK_COMMA}, {"[",  TK_LSQBR ,}, {"]", TK_RSQBR}, {";", TK_SEMICOLON}, {":", TK_COLON},
	{"..", TK_POINTPOINT}, {"(", TK_LROBR}, {")", TK_RROBR}, {"shr", TK_SHR}, {"shl", TK_SHL} };

Tokenizer::Tokenizer(string str) {
	data = str;
	index = -1;
	nextcol = 1;
	nextrow = 1;
}

void Tokenizer::inccol(char c, bool flag) {
	int j = 1;
	if (c == ' ') j = 1;
	if (c == '\t') j = 4 * (token.col / 4 + 1) + 1 - nextcol;
	nextcol += j;
	if (!flag) token.col += j;
	if (c == '\n') {
		nextrow++;
		nextcol = 1;
		if (!flag) {
			token.row++;
			token.col = 1;
		}
	}

}

Token Tokenizer::Next() {
	int i = initial_state;
	string result;
	token.col = nextcol;
	token.row = nextrow;
	while (i >= initial_state) {
		i = transition_table[i][chartostate(data[++index])];
		inccol(data[index], (i != initial_state));
		if (i != initial_state) result += data[index];
	}
	SetTocken(i, result.substr(0, result.size() - final_states[i].second));
	nextcol = max(1, nextcol - final_states[i].second);
	if (nextcol == 1) nextrow--;
	index -= final_states[i].second;
	if (token.type == TK_ERROR) throw CompileException(token.value, token);
	return token;
}

void Tokenizer::SetTocken(int i, string val) {
	token.value = val;
	token.type = final_states[i].first;
	if (token.type == TK_ERROR)
		token.value = errors[abs(i) - 2];
	else if (token.type == TK_UNKNOWN) 
		token.type = keyword[val] == TK_EOF ? TK_IDENT : keyword[val];
	else if (token.type == TK_STR) {
		token.value = val.substr(1, val.size() - 2);
		if (token.value.size() == 1) token.type = TK_CHAR;
	}
	else if (token.type == TK_UNOP || token.type == TK_BINOP || token.type == TK_SEP)
		token.type = keyword[val];

	else if (token.type == TK_CODE) {
		token.type = TK_CHAR;
		token.value = atoi(val.substr(1, val.size()).c_str());
	}
	else if (token.type == TK_EREAL) token.type = TK_REAL;
	else if (token.type == TK_HEX) token.type = TK_INT;
}

Token Tokenizer::Get() {
	return token;
}