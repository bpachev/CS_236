#include "../parser.h"

int main(int argc, char** argv)
{
  if (argc < 3)
  {
    cout << "Usage: infilename outfilename" << endl;
    return 0;
  }

  ofstream out;
  out.open(argv[2]);

  Parser* p = new Parser();
  try {
    p->parse(argv[1]);
  }
  catch (exception& e)
  {
    out << "Failure!" << endl;
    out << "  ";
    print_tok(p->curr,out);
    // cout << e.what() << endl;
    delete p;
    return 0;
  }
  out << "Success!" << endl;
  out << p->prog->toString();
  delete p;
  return 0;
}
