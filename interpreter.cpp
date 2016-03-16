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

  if (level != PROJ3)
  {
    out << "Rule Evaluation " << endl;
    db.addRules(p.prog->rules);
  }

  switch(level){
    case PROJ3:
     // do nothing
     cout << endl;
     break;
    case PROJ4:
     // use a dumb algorithm to add facts to the database
     db.bruteEvalRules(out);
     break;
    case PROJ5:
     // use a smart algorithm to add facts to the database
      db.smartEvalRules(out);
    default:
     break;
  }

  if (level != PROJ3) db.dump_relations(out);
  out << "Query Evaluation" << endl << endl;
  // evaluate queries
  db.evalQueries(p.prog->queries, out);
}
