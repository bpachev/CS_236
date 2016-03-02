#include "interpreter.h"

Interpreter::Interpreter()
{
 db = DatalogDatabase();
}

void Interpreter::run(char * infile, ostream& out, interpreter_level level)
{
  Parser p = Parser();
  p.parse(infile);
//  cout << p.prog->toString() << endl;
  db.addRelations(p.prog->schemes);
  out << "Scheme Evaluation" << endl << endl;
  db.loadFacts(p.prog->facts);
  out << "Fact Evaluation" << endl << endl;
  db.dump_relations(out);
//  cout << "loaded facts " << endl;
//  cout << "DB DUMP" << endl << db.toString() << endl;

  switch(level){
    case PROJ3:
     // do nothing
     cout << endl;
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
  out << "Query Evaluation" << endl << endl;
  // evaluate queries
  db.evalQueries(p.prog->queries, out);
}
