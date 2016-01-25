#include "token.h"
#include "scanner.h"

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

ofstream out;
ifstream in;

void Scanner::scan(char * filename, vector<tok>& token_list)
{
  gen_tok_list(filename, token_list);
}

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
  out << "(" << token_names[t.t] << ",\"" << t.s << "\","<< t.line << ")" << endl;
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

int cleanup_tokens(state_info& state)
{
  if (state.state == QUOTE_)
  {
    print_toks(state.toks);
    line_error(state.last_qoute_line);
    return 1;
  }
  else if (state.state == ID_)
  {
    handle_id(' ', state);
  }
  else if (state.state == COLON_)
  {
    handle_colon(' ', state);
  }
  return 0;
}

int gen_tok_list(char* filename, vector<tok>& toks)
{
	char c;
  state_info state;
  state.state = MASTER_;
  state.tstr = "";
  state.lines = 1;
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
        line_error(state.lines);
        in.close();
        return 1;
		}

    //increment line count if needed
    if (c == '\n') {
      state.lines++;
    }
	}

  in.close();
  //check for missing closing quote, unsaved ID, or colon
  if (cleanup_tokens(state)!=0) return 1; //error
  state.tstr = "";
  add_tok(state,END_FILE);
  toks = state.toks;
	return 0;
}

void line_error(int line)
{
  out << "Input Error on line " + to_string(line) << endl;
  out.close();
}

void die_with_msg(string msg)
{
  cout << msg << endl;
  in.close();
  out.close();
  exit(0);
}
