#include "parameter.h"

class Predicate{
public:
  vector<Parameter> params;
  string name;
  ~Predicate();
  string toString();
  void addParam(tok t);
}
