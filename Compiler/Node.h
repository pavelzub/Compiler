#pragma once
#include "leckser.h"
#include <iomanip>
#define ttab 4;

class Node {
protected:
	Token tk;
public:
	virtual void print(int offset) {};
	Node(Token atk) : tk(atk) {};
};

class BinOpNode : public Node {
	Node *left, *right;
public:
	BinOpNode(Token atk, Node* aleft, Node *aright) : Node(atk), left(aleft), right(aright) {};
	void print(int offset) { left->print(offset + 4); cout << setw(offset + tk.value.size()) <<  tk.value << endl; right->print(offset + 4); };
};

class ConstNode : public Node {
public:
	void print(int offset) {cout << setw(offset + tk.value.size()) << tk.value << endl; };
	ConstNode(Token atk) : Node(atk) {};
};

class UnOpNode : public Node {
	Node *left;
public:
	UnOpNode(Token atk, Node* aleft) : Node(atk), left(aleft) {};
	void print(int offset) { left->print(offset + 4); cout << setw(offset + tk.value.size()) << tk.value << endl;};
};

class FunctionalNode : public Node {
	Node* parent;
	vector<Node*> args;
public:
	FunctionalNode(Token atk, Node* aparent, vector<Node*> arg) : Node(atk), parent(aparent), args(arg) {};
	void print(int offset) {};
};

class ArrNode : public Node {
	Node* parent;
	vector<Node*> args;
public:
	ArrNode(Token atk, Node* aparent, vector<Node*> arg) : Node(atk), parent(aparent), args(arg) {};
	void print(int offset) {};
};

class StructNode : public Node {
	Node* parent;
	Node *left;
public:
	StructNode(Token atk, Node* aparent, Node* aleft) : Node(atk), parent(aparent), left(aleft) {};
	void print(int offset) { parent->print(offset + 4); cout << setw(offset + tk.value.size()) << tk.value << endl; left->print(offset + 4); };
};