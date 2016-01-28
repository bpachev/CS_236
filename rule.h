#include "predicate.h"
#include "token.h"

class Rule {
public:
  Predicate* result;
  vector<Predicate*> premises;
  void addPred(Predicate * pred);
  ~Rule();
  string toString();
  void setResult(Predicate * pred);
};
