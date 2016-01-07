#include <iostream>
#include <fstream>
using namespace std;

enum token {COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,
  COLON_DASH,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,END_FILE};

enum State {QUOTE,MASTER,ID,COLON};

int main(int argc, char** argv)
{
  if (argc<3)
  {
    cout << "Not enough arguments." << endl;
    exit(1);
  }

  ifstream infile;
  infile.open(argv[1]);
  char c,b;
  State state = DEFAULT;
  while (b=infile.get(c))
  {
    switch (state)
    {
      case DEFAULT:
        break;
      case MASTER:
        break;
      case ID:
        break;
      case COLON:
        break;
    }
    cout << c;
  }
  cout << "infile: " << argv[1] <<endl;
  cout << "outfile: " << argv[2] << endl;
}
