#ifndef interpreter_h
#define interpreter_h
#include "parser.h"
#include "datalogDatabase.h"

enum interpreter_level {PROJ3, PROJ4, PROJ5};

class Interpreter
{
public:
  DatalogDatabase db;
  Interpreter();
  void run(char * infile, ostream& out, interpreter_level level);
};


#endif
