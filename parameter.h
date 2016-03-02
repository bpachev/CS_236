#include "token.h"

class Parameter {
  public:
   string value;
   string name;
   Parameter(string v);
   Parameter(tok t);
   string toString();
   static bool isLiteral(string s);
};
