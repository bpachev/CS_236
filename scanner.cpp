#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum token {COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,
  COLON_DASH,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,END_FILE};

enum State {QUOTE_,MASTER_,ID_,COLON_}; // to not be confused with the token type

int main(int argc, char** argv)
{
  if (argc<3)
  {
    cout << "Not enough arguments." << endl;
    exit(1);
  }

  ifstream infile;
  infile.open(argv[1]);
  char c;
  State state = MASTER_;
  string tstr = "";
  while (infile.get(c))
  {
    switch (state)
    {
      case QUOTE_:
        tstr += c;
        if (c=='\'')
        {
          state = MASTER_;
          //do something to handle updating tstr
          cout << tstr << endl;
          tstr = "";
        }
        break;
      case MASTER_:

        if (c=='\'')
        {
          state = QUOTE_;
          tstr = "'";
        }
        break;
      case ID_:
        break;
      case COLON_:
        break;
    }
  }
//  cout << "infile: " << argv[1] <<endl;
//  cout << "outfile: " << argv[2] << endl;
}
