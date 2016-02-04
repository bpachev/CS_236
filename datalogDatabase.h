#ifndef datalogDatabase_h
#define datalogDatabase_h
#include "relation.h"

class DatalogDatabase {
public:
 vector<Relation> relations;
 void addRelations(vector<Predicate*>& schemeList);
 void loadFacts(vector<Predicate*>& factList);
 void evalQueries(vector<Predicate*>& queryList, ostream& out);

};

#endif
