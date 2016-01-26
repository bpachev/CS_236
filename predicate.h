#pragma once
#include "parameter.h"

class Predicate{
public:
  vector<Parameter*> params;
  string name;
  Predicate(string n);
  ~Predicate();
  string toString();
  void addParam(tok t);
};
