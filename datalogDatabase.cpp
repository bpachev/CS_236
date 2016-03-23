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

//create all the info needed to select, project, and rename in order to evaluate the given query
void make_query_info(Predicate* query, vector<Constraint>& constraints, vector<int>& projection_inds, vector<string>& new_names)
{
  vector<string> pnames = query->paramNames();
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
}

void DatalogDatabase::evalQuery(Predicate* query, ostream& out)
{
  vector<int> projection_inds;
  vector<string> new_names;
  Relation * r = relations[query->name];
  vector<string> pnames = query->paramNames();
  vector<Constraint> constraints;
  make_query_info(query, constraints, projection_inds, new_names);

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

void DatalogDatabase::fixed_point(vector<int> rule_inds, ostream &out)
{
  int ntuples = totalTuples();
  int lastTuples = -1;
  int nits = 0;

  while (ntuples != lastTuples)
  {
    for (size_t k = 0; k < rule_inds.size(); k++)
    {
      evaluateRule(rules[rule_inds[k]], out);
    }
    lastTuples = ntuples;
    ntuples = totalTuples();
    nits++;
  }
  out << endl;
}

// is the first dependant on the second?
bool isRuleDependant(Rule * first, Rule * second)
{
  for (size_t k = 0; k < first->premises.size(); k++)
  {
    if (second->result->name == first->premises[k]->name) return true;
  }
  return false;
}

void DatalogDatabase::smartEvalRules(ostream& out)
{
  int nrules = rules.size();
  graph depend_graph = graph(nrules);
  for (int i=0; i < nrules; i++)
  {
    for (int j = 0; j < nrules; j++)
    {
      //check if rule i depends on j
      if (isRuleDependant(rules[i], rules[j])) depend_graph.add_edge(i, j);
    }

  }

  //ouput dependancy graph
  out << "Dependency Graph" << endl;
  out << depend_graph.toString() << endl;
  out << "Reverse Graph" << endl;
  graph rg = depend_graph.reverse();
  out << rg.toString() << endl;
  vector<int> pnums = rg.DFSForest();
  out << "Postorder Numbers"  << endl;
  out << rg.pos_nums() << endl;
  out << "SCC Search Order" << endl;
  for (int i = 0; i < nrules; i++)
  {
    out << "  R" << pnums[nrules-i-1] << endl;
  }
  out<<endl;

  vector<vector<int>> comps = depend_graph.SCC();
  for (size_t c= 0; c < comps.size(); c++)
  {
    out << "SCC:";
    size_t csize = comps[c].size();
    for (size_t i = 0; i < csize; i++)
    {
      out << " R" << comps[c][i];
    }
    out << endl;
    if (csize == 1 && !depend_graph.has_edge(comps[c][0], comps[c][0]))
    {
      evaluateRule(rules[comps[c][0]], out);
      out << endl;
      continue;
    }
    fixed_point(comps[c], out);
  }
  out << "Rule Evaluation Complete" << endl << endl;
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
  out << r->toString() << endl;

  //step 2 init the first relation
  Predicate * first_pred = r->premises[0];
  vector<int> projection_inds1;
  vector<string> new_names1;
  vector<Constraint> constraints1;
  make_query_info(first_pred, constraints1, projection_inds1, new_names1);
  Relation res = relations[first_pred->name]->select(constraints1).project(projection_inds1).rename(new_names1);
//  cout << res.toString() << endl;
  for (size_t i = 1; i < r->premises.size(); i++)
  {
    Predicate * p = r->premises[i];
    vector<int> projection_inds;
    vector<string> new_names;
    vector<Constraint> constraints;
    make_query_info(p, constraints, projection_inds, new_names);
    Relation temp = relations[p->name]->select(constraints).project(projection_inds).rename(new_names);
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
