#include "token.h"
#include "rule.h"
#include <set>

class DatalogProgram {
public:
  vector<Predicate*> schemes;
  vector<Rule*> rules;
  vector<Predicate*> facts;
  vector<Predicate*> queries;
  set<string> domain;
  ~DatalogProgram();
  string toString();
  void add_dom_str(string s);
  void addScheme(Predicate* p);
  void addFact(Predicate* p);
  void addRule(Rule* r);
  void addQuery(Predicate* p);
  //utility functions
  void del_pred_list(vector<Predicate*>& l);
  string pred_list_str(string lname, vector<Predicate*>& l);
  string lheader(string lname, int lsize);
};
