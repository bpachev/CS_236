#include "datalogDatabase.h"


void DatalogDatabase::addRelations(vector<Predicate*>& schemeList){
  int i;
  for (i=0; i < schemeList.size(); i++)
  {
    Predicate * p = schemeList[i];
    Relation r = Relation(p->paramNames());
    cout << p->name << endl;
    relations[p->name] = &r;
  }
}

void DatalogDatabase::loadFacts(vector<Predicate*>& factList){
  int i;
  for (i = 0; i < factList.size(); i++)
  {
    Predicate * fact = factList[i];
    cout << fact->name << endl;
    Relation * r = relations[fact->name];
    cout << "added to map" << endl;
    r->add(fact->paramNames());
  }
}

void DatalogDatabase::evalQueries(vector<Predicate*>& queryList, ostream& out){

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
