#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>

using namespace std;

enum token {COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,
  COLON_DASH,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,END_FILE};

enum State {QUOTE_,MASTER_,ID_,COLON_,ERR_}; // to not be confused with the token type

struct tok
{
  int count;
  token t; //type
  string s; //token string
};

vector<string> token_names = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON",
  "COLON_DASH","SCHEMES","FACTS","RULES","QUERIES","ID","STRING","END_FILE"};

map<char, token> one_char_toks = {{'(',LEFT_PAREN}, {')',RIGHT_PAREN}, {'?', Q_MARK}, {',', COMMA}, {'.', PERIOD}};

State state_from_char(char c);
void add_tok(vector<tok>& toks,string tok_str,token tok_type);
vector<tok> tok_summary(vector<tok> toks)
void print_toks(vector<tok>& toks);
void print_tok(tok t);

vector<tok> gen_tok_list(ifstream in);

//state_from_char assumes that c was the next character after a token ended.
//An example situation is when an ID is followed by a comma, ending the token
// This function determines the new state and performs any needed actions (like adding the comma).
State state_from_char(char c, vector<tok>& toks,string & tstr)
{
	tstr = ""+c; // if we just finished a token, tstr should reset
	if (c==':') return COLON_;
	}

	if (one_char_toks.find(c) != one_char_toks.end())
	{
		add_tok(toks, ""+c, one_char_toks[c]);
		return MASTER_;
	}

	if (isspace(c)) return MASTER_;

	if (c == '\'') return QUOTE_;

	if (isalpha(c)) return ID_;

	return ERR_; // not a whitespace separator, but not the start of a valid token
}

void add_tok(vector<tok>& toks,string tok_str,token tok_type)
{
  tok temp;
  temp.s = tok_str;
  temp.t = tok_type;
  temp.count = 1;
  toks.push_back(temp);
}

vector<tok> tok_summary(vector<tok> toks)
{
	vector<tok> res;
	for (unsigned int i=0; i < toks.size(); i++)
	{
		if (!toks[i].count)
		{
			continue;
		}
		else
		{
			string s = toks[i].s;
			for (unsigned int j = i+1;j<toks.size();j++)
			{
				if (toks[j].s == s)
				{
					toks[i].count++;
					toks[j].count = 0;
				}
			}
			res.push_back(toks[i]);
		}
  }
  return res;
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

vector<tok> gen_tok_list(ifstream in)
{
	char c;
	int lines = 1;
	State state = MASTER_;
	string tstr = "";
	vector<tok> toks;

	while (infile.get(c))
	{
		if (c == '\n') lines++;
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
				state = state_from_char(c,toks,tstr);
				break;
			case ID_: // we are in the process of reading an ID
				if (!isalnum(c))
				{
					add_tok(toks,tstr,ID);
					state = state_from_char(c,toks,tstr);
				}
				else tstr += c;
				break;
			case COLON_:
				if (c == '-')
				{
					tstr = "";
					//append token to my data structure
					add_tok(toks,":-",COLON_DASH);
					state = MASTER_; //wait for another token to begin ...
				}
				else
				{
					//write out colon token to my data structure (token list)
					add_tok(toks,":",COLON);
					state = state_from_char(c,toks,tstr);
				}
				break;
			case ERR_:
				//halt execution, print error message
				vector<tok> tok_sum = tok_summary(toks);
				print_toks(tok_sum);
				cout << "error on line " << lines << endl;
				exit(1);
				break;
		}
	}
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
	vector<tok> toks = gen_tok_list(infile);
	unsigned int num_toks = toks.size();
	print_toks(toks);
	toks = tok_summary(toks);
	print_toks(toks);
	cout << "Total Tokens = " << num_toks << endl;
}
