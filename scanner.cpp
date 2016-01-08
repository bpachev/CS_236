#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>

using namespace std;

enum token {COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,
  COLON_DASH,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,END_FILE};

enum State {QUOTE_,MASTER_,ID_,COLON_,COMMENT_,ERR_}; // to not be confused with the token type

struct tok
{
  int line;
  token t; //type
  string s; //token string
};

struct state_info
{
  vector<tok> toks;
  State state;
  string tstr;
  int lines;
  int last_qoute_line;
};

vector<string> token_names = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON",
  "COLON_DASH","SCHEMES","FACTS","RULES","QUERIES","ID","STRING","EOF"};

map<char, token> one_char_toks = {{'(',LEFT_PAREN}, {')',RIGHT_PAREN}, {'?', Q_MARK}, {',', COMMA}, {'.', PERIOD}};

map<string, token> keywords = {{"Schemes",SCHEMES},{"Facts",FACTS},{"Rules",RULES},{"Queries",QUERIES}};

void state_from_char(char c, state_info& state);
void set_new_state(char c, state_info& state);
void add_tok(state_info& state,token tok_type);
void print_toks(vector<tok>& toks);
void print_tok(tok t);
vector<tok> gen_tok_list(char* filename);
void handle_id(char c, state_info& state);
void handle_colon(char c, state_info& state);
void handle_quote(char c, state_info& state);
void set_new_state(char c, state_info& state);
void cleanup_tokens(state_info& state);


//state_from_char assumes that c was the next character after a token ended.
//An example situation is when an ID is followed by a comma, ending the token
// This function determines the new state and performs any needed actions (like adding the comma).
void state_from_char(char c, state_info& state)
{
	state.tstr = ""; // if we just finished a token, tstr should reset
	state.tstr += c;
	if (c==':') state.state = COLON_;
	else if (one_char_toks.find(c) != one_char_toks.end())
	{
		add_tok(state, one_char_toks[c]);
		state.state = MASTER_;
	}
  else set_new_state(c, state);
}

void set_new_state(char c, state_info& state)
{
	if (isspace(c)) state.state = MASTER_;
	else if (c == '\'')
  {
    state.state = QUOTE_;
    state.last_qoute_line = state.lines;
  }
	else if (isalpha(c)) state.state = ID_;
  else if (c == '#') state.state = COMMENT_; //start of comment
	else state.state = ERR_; // not a whitespace separator, but not the start of a valid token
}

void add_tok(state_info& state,token tok_type)
{
  tok temp;
  temp.s = state.tstr;
  temp.t = tok_type;
  temp.line = state.lines;
  (state.toks).push_back(temp);
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
  cout << "(" << token_names[t.t] << ",\"" << t.s << "\","<< t.line << ")" << endl;
}

void handle_id(char c, state_info& state)
{
  if (!isalnum(c))
  {
    if (keywords.find(state.tstr) != keywords.end())
    {
      add_tok(state,keywords[state.tstr]);
    }
    else add_tok(state,ID);
    state_from_char(c,state);
  }
  else state.tstr += c;
}

void handle_colon(char c, state_info& state)
{
  if (c == '-')
  {
    state.tstr = ":-";
    //append token to my data structure
    add_tok(state,COLON_DASH);
    state.state = MASTER_; //wait for another token to begin ...
  }
  else
  {
    //write out colon token to my data structure (token list)
    state.tstr = ":";
    add_tok(state,COLON);
    state_from_char(c,state);
  }
}

void handle_quote(char c, state_info& state)
{
  state.tstr += c;
  if (c=='\'')
  {
    state.state = MASTER_;
    //do something to handle updating tstr
    add_tok(state,STRING);
    state.tstr = "";
  }
}

void cleanup_tokens(state_info& state)
{
  if (state.state == QUOTE_)
  {
    print_toks(state.toks);
    cout << "Input Error on line " << state.last_qoute_line << endl;
    exit(1);
  }
  else if (state.state == ID_)
  {
    handle_id(' ', state);
  }
  else if (state.state == COLON_)
  {
    handle_colon(' ', state);
  }
}

vector<tok> gen_tok_list(char* filename)
{
	char c;
  state_info state;
  state.state = MASTER_;
  state.tstr = "";
  state.lines = 1;
	ifstream in;
	in.open(filename);

	while (in.get(c))
	{
		switch (state.state)
		{
			case QUOTE_:
        handle_quote(c,state);
				break;
			case MASTER_:
				state_from_char(c,state);
				break;
			case ID_: // we are in the process of reading an ID
        handle_id(c, state);
				break;
			case COLON_:
        handle_colon(c,state);
				break;
      case COMMENT_:
        if (c=='\n') state.state = MASTER_;
        break;
			case ERR_:
				//halt execution, print error message
				print_toks(state.toks);
				cout << "Input Error on line " << state.lines << endl;
				exit(1);
				break;
		}

    //increment line count if needed
    if (c == '\n') {
      state.lines++;
    }
	}

  //check for missing closing quote, unsaved ID, or colon
  cleanup_tokens(state);
  state.tstr = "";
  add_tok(state,END_FILE);
	return state.toks;
}

void die_with_msg(string msg)
{
  cout << msg << endl;
  exit(1);
}

int main(int argc, char** argv)
{
	if (argc<2)
	{
		die_with_msg("Not enough arguments. You must provide a valid infile.");
	}

	vector<tok> toks = gen_tok_list(argv[1]);
	print_toks(toks);
	cout << "Total Tokens = " << toks.size() << endl;
}
