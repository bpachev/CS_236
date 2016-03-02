#ifndef datalogDatabase_h
#define datalogDatabase_h
#include "relation.h"
#include <map>

class DatalogDatabase {
public:
 map<string, Relation*> relations;
 void addRelations(vector<Predicate*>& schemeList);
 void loadFacts(vector<Predicate*>& factList);
 void evalQueries(vector<Predicate*>& queryList, ostream& out);
 string toString();
};

#endif
