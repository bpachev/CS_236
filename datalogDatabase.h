#ifndef datalogDatabase_h
#define datalogDatabase_h
#include "relation.h"
#include "graph.h"
#include <map>

using namespace std;
class DatalogDatabase {
public:
 map<string, Relation*> relations;
 vector<Rule*> rules;

 ~DatalogDatabase();
 void addRelations(vector<Predicate*>& schemeList);
 void loadFacts(vector<Predicate*>& factList);
 void evalQueries(vector<Predicate*>& queryList, ostream& out);
 string toString();
 void evalQuery(Predicate* query, ostream& out);
 void addRules(vector<Rule*> ruleList);
 void dump_relations(ostream& out);
 void dump_rules(ostream& out);
 void bruteEvalRules(ostream& out);
 void smartEvalRules(ostream& out);
 int totalTuples();
 void evaluateRule(Rule* r, ostream& out);
 void fixed_point(vector<int> rule_inds, ostream &out);
};

#endif
