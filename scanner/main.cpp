#include "../scanner.h"


int main(int argc, char** argv)
{
	if (argc<3)
	{
		cout << "Not enough arguments. You must provide a valid infile." << endl;
		return 0;
	}

	ofstream out;
  out.open(argv[2]);
	Scanner* s = new Scanner();
	try
	{
 		s->scan(argv[1]);
		print_toks(s->toks,out);
		out << "Total Tokens = " << s->toks.size() << endl;
  	out.close();
		delete s;
	}
	catch (exception& e)
	{
		print_toks(s->toks, out);
		// cout << e.what();
		out << e.what();
		out.close();
		delete s;
	}
}
