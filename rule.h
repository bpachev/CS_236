"include predicate.h"

class Rule {
public:
 Predicate result;
 vector<Predicate*> premises;
 void Rule::addPred(Predicate * pred)
 string toString();
}
