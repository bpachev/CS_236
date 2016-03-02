#include "datalogDatabase.h"


void DatalogDatabase::addRelations(vector<Predicate*>& schemeList){
  int i;
  for (i=0; i < schemeList.size(); i++)
  {
    schemeList[i]->;
  }
}

void DatalogDatabase::loadFacts(vector<Predicate*>& factList){

}

void DatalogDatabase::evalQueries(vector<Predicate*>& queryList, ostream& out){

}
