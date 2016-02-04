#include "interpreter.h"

Interpreter::Interpreter()
{
 db = datalogDatabase();
}

void Interpreter::run(char * infile, ofstream out, interpreter_level level)
{
  Parser p = Parser();
  p.parse(char* infile);
  db.addRelations(p.prog->schemeList);
  db.loadFacts(p.prog->factList);

  switch(interpreter_level){
    case PROJ3:
     // do nothing
     break;
    case PROJ4:
     // use a dumb algorithm to add facts to the database
     // db.bruteAddRules(p.prog->ruleLust)
     break;
    case PROJ5:
     // use a smart algorithm to add facts to the database
     // db.smartAddRules(p.prog->ruleList)
    default:
     break;
  }

  // evaluate queries
  db.evalQueries(p.prog->queryList, out);
}

void Interpreter::load
