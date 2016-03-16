#include "interpreter.h"

int main (int argc, char** argv)
{
  if (argc < 3)
  {
    cout << "Usage infile outfile." << endl;
    return 0;
  }

  ofstream out;
  out.open(argv[2]);

  Interpreter i = Interpreter();
  i.run(argv[1], out, PROJ4);
}
