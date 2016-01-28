#ifndef parser_h
#define parser_h
#include "scanner.h"
#include "datalogProgram.h"

class Parser
{
 public:
   void parse(char * infile);
   tok curr;
   DatalogProgram* prog;
 	 vector<Predicate*> predList;
   Predicate* last_pred;
   ~Parser();

 private:
   vector<tok> toks;
   vector<tok>::iterator it;
   void datalogProgram();
   void schemeList();
   void factList();
   void queryList();
   void ruleList();
   void scheme();
   void fact();
   void rule();
   void query();
   void predicateList();
   void predicate();
   void parameterList();
   void parameter();
   void match(token t);
};
#endif
