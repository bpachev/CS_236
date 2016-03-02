#ifndef Constraint_h
#define Constraint_h
#include <vector>
#include <string>
using namespace std;

class Constraint
{
public:
  string val;
  int ind;
  int indexInTuple;
  //two columns are constrained to be equal
  Constraint(int indexInTuple, int index);
  //two rows are constrained to be equal
  Constraint(int indexInTuple, string value);
  bool isMet(vector<string>& tuple);
  string toString();
};
#endif
