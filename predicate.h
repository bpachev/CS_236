#ifndef parameter_h
#define parameter_h
#include "parameter.h"

class Predicate{
public:
  vector<Parameter*> params;
  string name;
  Predicate(string n);
  ~Predicate();
  string toString();
  vector<string> paramNames();
  void addParam(tok t);
};
#endif
