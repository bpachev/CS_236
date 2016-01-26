#include "datalogProgram.h"

string DatalogProgram::toString()
{
  string res = pred_list_str("Schemes", schemes);
  res += pred_list_str("Facts", facts);
  res += lheader("Rules", rules);

  for (int i = 0; i < rules.size(); i++) {
    res += "  ";
    res += rules[i].toString();
  }

  res += pred_list_str("Queries", queries);

  for (int k = 0; k < domain.size(); k++)
  {
    res += domain[k];
  }

  set<string>::iterator it;
  for (it = domain.begin(); it != domain.end(); ++it)
  {
    res += *it;
  }
  return res;
}

DatalogProgram::~DatalogProgram()
{
  del_pred_list(schemes);
  del_pred_list(facts);
  del_pred_list(queries);
  for (int i = 0; i < rules.size(); i++)
  {
    delete rules[i];
  }
}

string DatalogProgram::lheader(string lname, int lsize)
{
  string res = lname;
  res += "(";
  res += to_string(lsize);
  res += "):\n";
  return res;
}

string DatalogProgram::pred_list_str(vector<Predicate>& l)
{
  string res = lheader(lname, l.size());
  for (int i = 0; i < res.size(); i++)
  {
    res += "  ";
    res += l[i].toString();
  }
  return res;
}

void DatalogProgram::del_pred_list(vector<Predicate>& l)
{
  for (int i = 0; i < l.size(); i++)
  {
    delete l[i];
  }
}

void DatalogProgram::add_dom_str(string s)
{
  domain.insert(s);
}
