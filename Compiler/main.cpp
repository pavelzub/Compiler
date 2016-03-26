#include "leckser.h"
#include "parser.h"
#include <iomanip>


int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Wrong number of parametrs\n");
		exit(1);
	}
	ifstream fin(argv[1]);
	string str;
	if (!fin.is_open()) {
		cout << "Can't open file " << argv[1] << endl;
		return 0;
	}
	else getline(fin, str, '\0');

	Tokenizer tokenizer(str);
		
	try {
		ParseExp pars(tokenizer);
		pars.Parse();
		/*while (tokenizer.Next().type != TK_EOF) {
			Token tk = tokenizer.Get();
			cout << tk.row << '\t' << tk.col << '\t' << tk.description() << '\t' << tk.value << endl;
		}*/
		pars.Print();
	}
	catch (CompileException& e)
	{
		e.print();
	}
	return 0;
	
}