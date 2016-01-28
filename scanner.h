#ifndef scanner_h
#define scanner_h
#include <stdexcept>
#include "token.h"

void print_toks(vector<tok>& toks, ostream& o);
void print_tok(tok t, ostream& o);


class Scanner
{
public:
  State state;
  string tstr;
  vector<tok> toks;
  int lines;
  int last_qoute_line;
  void scan(char * filename);
  void gen_tok_list(char* filename);
  void handle_id(char c);
  void handle_colon(char c);
  void handle_quote(char c);
  int cleanup_tokens(void);
  void line_error(int line);
  void state_from_char(char c);
  void set_new_state(char c);
  void add_tok(token tok_type);
};
#endif
