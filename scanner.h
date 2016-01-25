void state_from_char(char c, state_info& state);
void set_new_state(char c, state_info& state);
void add_tok(state_info& state,token tok_type);
void print_toks(vector<tok>& toks);
void print_tok(tok t);
int gen_tok_list(char* filename,vector<tok>& toks);
void handle_id(char c, state_info& state);
void handle_colon(char c, state_info& state);
void handle_quote(char c, state_info& state);
void set_new_state(char c, state_info& state);
int cleanup_tokens(state_info& state);
void line_error(int line);
void die_with_msg(string msg);


public Scanner
{
 void scan(char * filename, vector<tok>& token_list);
}
