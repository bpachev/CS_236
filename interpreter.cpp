#include "interpreter.h"

Interpreter::Interpreter()
{
 db = DatalogDatabase();
}

void Interpreter::run(char * infile, ostream& out, interpreter_level level)
{
  Parser p = Parser();
  p.parse(infile);
  cout << p.prog->toString() << endl;
  db.addRelations(p.prog->schemes);
  cout << "added relations " << endl;
  db.loadFacts(p.prog->facts);
  cout << "loaded facts " << endl;
  cout << "DB DUMP" << endl << db.toString() << endl;

  switch(level){
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
  db.evalQueries(p.prog->queries, out);
}
