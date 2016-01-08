#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

enum token {COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,
  COLON_DASH,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,END_FILE};

enum State {QUOTE_,MASTER_,ID_,COLON_}; // to not be confused with the token type

struct tok
{
  int count;
  token t; //type
  string s; //token string
};

vector<string> token_names = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON",
  "COLON_DASH","SCHEMES","FACTS","RULES","QUERIES","ID","STRING","END_FILE"};

void add_tok(vector<tok>& toks,string tok_str,token tok_type);
void print_toks(vector<tok>& toks);
void print_tok(tok t);


void add_tok(vector<tok>& toks,string tok_str,token tok_type)
{
  for (unsigned int i=0; i < toks.size(); i++)
  {
    if (toks[i].s == tok_str)
    {
      toks[i].count++;
      return;
    }
  }

  tok temp;
  temp.s = tok_str;
  temp.t = tok_type;
  temp.count = 1;
  toks.push_back(temp);
//  cout << toks.size() << endl;
}

void print_toks(vector<tok>& toks)
{
  for (unsigned int i = 0; i < toks.size(); i++)
  {
    print_tok(toks[i]);
  }
}

void print_tok(tok t)
{
  cout << "(" << token_names[t.t] << ",\"" << t.s << "\","<< t.count << ")" << endl;
}

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
  vector<tok> toks;

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
          add_tok(toks,tstr,STRING);
          cout << toks.size() << endl;          
          tstr = "";
        }
        break;
      case MASTER_:

        if (c=='\'')
        {
          tstr = "'";
          state = QUOTE_;
        }
        break;
      case ID_:
        break;
      case COLON_:
        if (c == '-')
        {
          tstr = ":-";
          //append token to my data structure ...
          add_tok(toks,tstr,COLON_DASH);
        }
        else
        {
          tstr = ":";
          //write out colon token to my data structure
          add_tok(toks,tstr,COLON);
        }
        break;
    }
  }
  cout << toks.size() << endl;
  print_toks(toks);
//  cout << "infile: " << argv[1] <<endl;
//  cout << "outfile: " << argv[2] << endl;
}
