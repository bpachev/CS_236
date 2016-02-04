#ifndef Relation_h
#define Relation_h
#include "datalogProgram.h"
#include <algorithm>

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
};

struct tupleCompare
{
 bool operator()(const vector<string>& A, const vector<string>& B) const
 {
   int l = A.size();
   for (int i = 0; i < l; i++)
   {
     if (A[i] < B[i]) return true;
     else if (A[i] > B[i]) return false;
   }
   return false;
 }
};

class Relation
{
public:
 vector<string> columns;
 vector<vector<string>> tuples;
 Relation(vector<string> col_names);
 Relation select(vector<Constraint>& constraints);
 Relation project(vector<int>& newInds);
 Relation rename(vector<string> newNames);
 int size();
 string toString();
};

string tuple_to_string(vector<string>& t);

#endif
