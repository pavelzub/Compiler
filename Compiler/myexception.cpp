#include "myexception.h"

void CompileException::print() const {
	if (row != -1)
		cout << "ERROR: " << massage << "\t at line " << row << ", column " << col << endl;
	else
		cout << "ERROR: " << massage << endl;
}