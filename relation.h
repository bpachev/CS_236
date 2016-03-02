#ifndef Relation_h
#define Relation_h
#include "datalogProgram.h"
#include "constraint.h"
#include <algorithm>


struct tupleCompare
{
 bool operator()(const vector<string>& A, const vector<string>& B)
 {
   cout << "Called compare" << endl;
   int lA = A.size();
   int lB = B.size();
   for (int i = 0; i < lA; i++)
   {
     cout << lB << "comparing " << A[i] << " to " << B[i] << endl;
     if (i >= lB) return false;
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
 set<vector<string>, tupleCompare> tuples;
 Relation(vector<string> col_names);
 Relation select(vector<Constraint>& constraints);
 Relation project(vector<int>& newInds);
 Relation rename(vector<string> newNames);
 void add(vector<string> v);
 int size();
 string toString();
};

string tuple_to_string(vector<string>& t);


#endif
