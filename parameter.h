#include "token.h"

class Parameter {
  public:
   string value;
   string name;
   Parameter(string v);
   Parameter(tok t);
   string toString();
};
