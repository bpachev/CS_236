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
