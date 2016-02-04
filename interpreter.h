#include "parser.h"
#include "datalogDatabase.h"
#ifndef interpreter_h
#define interpreter_h

enum intepreter_level {PROJ3, PROJ4, PROJ5};

class Interpreter:
{
public:
  datalogDatabase db;
  Interpreter();
  void run(ifstream in, ofstream out, interpreter_level level);
};


#endif
