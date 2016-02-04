#include "relation.h"
#ifndef datalogDatabase_h
#define datalogDatabase_h

class DatalogDatabase {
public:
 vector<Relation> relations;
 void addRelations(vector<Predicate*>& schemeList);
 void loadFacts(vector<Predicate*>& factList);
 void evalQueries(vector<Predicate*>& queryList);

};

#endif
