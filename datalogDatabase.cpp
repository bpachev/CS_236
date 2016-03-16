#include "datalogDatabase.h"

void DatalogDatabase::addRelations(vector<Predicate*>& schemeList){
  unsigned int i;
  for (i=0; i < schemeList.size(); i++)
  {
    Predicate * p = schemeList[i];
    Relation* r = new Relation(p->paramNames());
//    cout << p->name << endl;
    relations[p->name] = r;
  }
}

void DatalogDatabase::loadFacts(vector<Predicate*>& factList){
  unsigned int i;
  for (i = 0; i < factList.size(); i++)
  {
    Predicate * fact = factList[i];
//    cout << fact->name << endl;
    Relation * r = relations[fact->name];
  //  cout << "added to map" << endl;
    r->add(fact->paramNames());
  }
}

void print_contraints(vector<Constraint> c)
{
  for (unsigned int i=0; i < c.size(); i++)
  {
    cout << c[i].toString() << " ";
  }
  cout << endl;
}

void DatalogDatabase::evalQuery(Predicate* query, ostream& out)
{
  vector<int> projection_inds;
  vector<string> new_names;
  Relation * r = relations[query->name];
  vector<string> pnames = query->paramNames();
  vector<Constraint> constraints;
  for (unsigned int j =0; j < pnames.size(); j++)
  {
    if (Parameter::isLiteral(pnames[j]))
    {
      constraints.push_back(Constraint(j, pnames[j]));
      continue;
    }
    //check to see if we have seen this before
    unsigned int most_recent_occur = j;
    for (int k = j-1; k >=0; k--)
    {
      if (pnames[k] == pnames[j])
      {
        constraints.push_back(Constraint(j, k));
        most_recent_occur = k;
        break;
      }
    }

    //if this is the first occurance
    if (most_recent_occur == j)
    {
      projection_inds.push_back(j);
      new_names.push_back(pnames[j]);
    }
  }
  out << query->toString() << "?";
//    print_contraints(constraints);
  Relation res = r->select(constraints);
  unsigned int result_size = res.size();
  if (result_size == 0)
  {
    out << " No" << endl;
    return;
  }
  else out << " Yes(" << result_size << ")" << endl;

  out << "select" << endl << res.toString();
  Relation projected = res.project(projection_inds);
  if (projected.size() == 0)
  {
    out << "project\nrename" << endl;
    return;
  }
  out << "project" << endl << projected.toString();
  Relation renamed = projected.rename(new_names);
  out <<"rename" << endl << renamed.toString();
}

void DatalogDatabase::evalQueries(vector<Predicate*>& queryList, ostream& out){
//  cout << queryList.size() << endl;
  for (unsigned int i = 0; i < queryList.size(); i++)
  {
    evalQuery(queryList[i], out);
    out << endl;
  }
}

void DatalogDatabase::dump_relations(ostream& out)
{
  for (auto const & pair: relations)
  {
    out << pair.first << endl;
    out << pair.second->toString() << endl;
  }
}

void DatalogDatabase::addRules(vector<Rule*> ruleList)
{
  //for each rule, I get the name (as an index into stuff)
  rules = ruleList;
}

void DatalogDatabase::dump_rules(ostream& out)
{
  for (size_t k = 0; k < rules.size(); k++)
  {
    out << rules[k]->toString() << endl << endl;
  }
}

void DatalogDatabase::bruteEvalRules(ostream& out)
{
  int ntuples = totalTuples();
  int lastTuples = -1;
  int nits = 0;

  while (ntuples != lastTuples)
  {
    for (size_t k = 0; k < rules.size(); k++)
    {
      evaluateRule(rules[k], out);
    }
    lastTuples = ntuples;
    ntuples = totalTuples();
    nits++;
  }

  out << endl << "Converged after " << nits << " passes through the Rules." << endl << endl;
}

void DatalogDatabase::smartEvalRules(ostream& out)
{

}

int DatalogDatabase::totalTuples()
{
  int res = 0;
  for (auto const & pair: relations)
  {
    res += pair.second->size();
  }
  return res;
}

//beware of stack smashing
void DatalogDatabase::evaluateRule(Rule* r, ostream& out)
{
  //step 1 determine the relation to be updated
//  cout << "evaluating rule "+r->toString() << endl;
  Relation * target = relations[r->result->name];
  out << target->toString() << endl;

  //step 2 init the first relation
  Predicate * first_pred = r->premises[0];
  Relation res = relations[first_pred->name]->rename(first_pred->paramNames());
//  cout << res.toString() << endl;
  for (size_t i = 1; i < r->premises.size(); i++)
  {
    Predicate * p = r->premises[i];
    Relation temp = relations[p->name]->rename(p->paramNames());
    res = res.join(temp);
//    cout << temp.toString() << endl;
//    cout << res.toString() << endl;
  }

  res = res.project(r->result->paramNames());
//  cout << res.toString();
  target->unionWith(res, out);
}

string DatalogDatabase::toString()
{
 string res = "";
 for (auto const & pair: relations)
 {
   res += pair.first; // name
   res += " ";
   res += pair.second->toString(); //relation
 }
 return res;
}

DatalogDatabase::~DatalogDatabase()
{
  for (auto const & pair: relations)
  {
    delete pair.second; //relation
  }
}
