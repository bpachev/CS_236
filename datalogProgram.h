"include parameter.h"

class DatalogProgram {
public:
  vector<Predicate> schemes;
  vector<Rule> rules;
  vector<Predicate> facts;
  vector<Predicate> queries;
  set<string> domain;
  ~DatalogProgram();
  string toString();
  void add_dom_str(string s);
  void del_pred_list(vector<Predicate>& l);
  string pred_list_str(vector<Predicate>& l);
  string lheader(string lname, int lsize);
};
