#include "../parser.h"

int main(int argc, char** argv)
{
  ofstream out;
//  out.open(argv[2]);
  Parser* p = new Parser();
  try {
    p->parse(argv[1]);
  }
  catch (exception e)
  {
    cout << e.what();
  }
  cout << "Hello World." << endl;
}
