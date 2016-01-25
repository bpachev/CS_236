#include "scanner.h"

class Parser
{
 public:
   void parse(char * infile);
   tok curr;
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
