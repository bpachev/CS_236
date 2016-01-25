#include "scanner.h"


vector<string> token_names = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON",
  "COLON_DASH","SCHEMES","FACTS","RULES","QUERIES","ID","STRING","EOF"};

map<char, token> one_char_toks = {{'(',LEFT_PAREN}, {')',RIGHT_PAREN}, {'?', Q_MARK}, {',', COMMA}, {'.', PERIOD}};

map<string, token> keywords = {{"Schemes",SCHEMES},{"Facts",FACTS},{"Rules",RULES},{"Queries",QUERIES}};

void Scanner::scan(char * filename)
{
  gen_tok_list(filename);
}


//state_from_char assumes that c was the next character after a token ended.
//An example situation is when an ID is followed by a comma, ending the token
// This function determines the new state and performs any needed actions (like adding the comma).
void Scanner::state_from_char(char c)
{
	tstr = ""; // if we just finished a token, tstr should reset
	tstr += c;
	if (c==':') state = COLON_;
	else if (one_char_toks.find(c) != one_char_toks.end())
	{
		add_tok(one_char_toks[c]);
		state = MASTER_;
	}
  else set_new_state(c);
}

void Scanner::set_new_state(char c)
{
	if (isspace(c)) state = MASTER_;
	else if (c == '\'')
  {
    state = QUOTE_;
    last_qoute_line = lines;
  }
	else if (isalpha(c)) state = ID_;
  else if (c == '#') state = COMMENT_; //start of comment
	else state = ERR_; // not a whitespace separator, but not the start of a valid token
}

void Scanner::add_tok(token tok_type)
{
  tok temp;
  temp.s = tstr;
  temp.t = tok_type;
  temp.line = lines;
  (toks).push_back(temp);
}

void print_toks(vector<tok>& toks,  ostream& s)
{
  for (unsigned int i = 0; i < toks.size(); i++)
  {
    print_tok(toks[i], s);
  }
}

void print_tok(tok t, ostream& s)
{
  s << "(" << token_names[t.t] << ",\"" << t.s << "\","<< t.line << ")" << endl;
}

void Scanner::handle_id(char c)
{
  if (!isalnum(c))
  {
    if (keywords.find(tstr) != keywords.end())
    {
      add_tok(keywords[tstr]);
    }
    else add_tok(ID);
    state_from_char(c);
  }
  else tstr += c;
}

void Scanner::handle_colon(char c)
{
  if (c == '-')
  {
    tstr = ":-";
    //append token to my data structure
    add_tok(COLON_DASH);
    state = MASTER_; //wait for another token to begin ...
  }
  else
  {
    //write out colon token to my data structure (token list)
    tstr = ":";
    add_tok(COLON);
    state_from_char(c);
  }
}

void Scanner::handle_quote(char c)
{
  tstr += c;
  if (c=='\'')
  {
    state = MASTER_;
    //do something to handle updating tstr
    add_tok(STRING);
    tstr = "";
  }
}

int Scanner::cleanup_tokens(void)
{
  if (state == QUOTE_)
  {
    line_error(last_qoute_line);
  }
  else if (state == ID_)
  {
    handle_id(' ');
  }
  else if (state == COLON_)
  {
    handle_colon(' ');
  }
  return 0;
}

void Scanner::gen_tok_list(char* filename)
{
  ifstream in;
	char c;
  state = MASTER_;
  tstr = "";
  lines = 1;
  toks.clear();
	in.open(filename);

	while (in.get(c))
	{
		switch (state)
		{
			case QUOTE_:
        handle_quote(c);
				break;
			case MASTER_:
				state_from_char(c);
				break;
			case ID_: // we are in the process of reading an ID
        handle_id(c);
				break;
			case COLON_:
        handle_colon(c);
				break;
      case COMMENT_:
        if (c=='\n') state = MASTER_;
        break;
			case ERR_:
				//halt execution, print error message
        in.close();
        line_error(lines);
		}

    //increment line count if needed
    if (c == '\n') {
      lines++;
    }
	}

  in.close();
  //check for missing closing quote, unsaved ID, or colon
  cleanup_tokens(); //error
  tstr = "";
  add_tok(END_FILE);
}

void Scanner::line_error(int line)
{
  string error = "Input Error on line " + to_string(line);
  error += '\n';
  throw runtime_error(error);
}
