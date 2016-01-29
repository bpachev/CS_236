#include "datalogProgram.h"

string DatalogProgram::toString()
{
  string res = pred_list_str("Schemes", schemes);
  res += pred_list_str("Facts", facts);
  res += lheader((string)"Rules", rules.size());

  for (unsigned int i = 0; i < rules.size(); i++) {
    res += "  ";
    res += rules[i]->toString();
    res += "\n";
  }

  res += pred_list_str("Queries", queries);

  res += lheader("Domain", domain.size());
  set<string>::iterator it;
  for (it = domain.begin(); it != domain.end(); ++it)
  {
    res += "  ";
    res += *it;
    res += "\n";
  }
  return res;
}

DatalogProgram::~DatalogProgram()
{
  del_pred_list(schemes);
  del_pred_list(facts);
  del_pred_list(queries);
  for (unsigned int i = 0; i < rules.size(); i++)
  {
    delete rules[i];
  }
}

void DatalogProgram::addScheme(Predicate* p){
  schemes.push_back(p);
}

void DatalogProgram::addFact(Predicate* p){
  facts.push_back(p);
}

void DatalogProgram::addRule(Rule* r){
  rules.push_back(r);
}

void DatalogProgram::addQuery(Predicate* p){
  queries.push_back(p);
}

string DatalogProgram::lheader(string lname, int lsize)
{
  string res = lname;
  res += "(";
  res += to_string(lsize);
  res += "):\n";
  return res;
}

string DatalogProgram::pred_list_str(string lname, vector<Predicate*>& l)
{
  string res = lheader(lname, l.size());
  for (unsigned int i = 0; i < l.size(); i++)
  {
    res += "  ";
    res += l[i]->toString();
    res += "\n";
  }
  return res;
}

void DatalogProgram::del_pred_list(vector<Predicate*>& l)
{
  for (unsigned int i = 0; i < l.size(); i++)
  {
    delete l[i];
  }
}

void DatalogProgram::add_dom_str(string s)
{
  domain.insert(s);
}
