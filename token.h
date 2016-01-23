#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>

enum token {COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,
  COLON_DASH,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,END_FILE};

enum State {QUOTE_,MASTER_,ID_,COLON_,COMMENT_,ERR_}; // to not be confused with the token type

using namespace std;

struct tok
{
  int line;
  token t; //type
  string s; //token string
};
