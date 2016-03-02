#ifndef Relation_h
#define Relation_h
#include "datalogProgram.h"
#include "constraint.h"
#include "tuple.h"
#include <algorithm>


struct tupleCompare
{
 bool operator()(const Tuple& A, const Tuple& B)
 {
//   cout << "Called compare" << endl;
   int lA = A.data.size();
   int lB = B.data.size();
   for (int i = 0; i < lA; i++)
   {
    // cout << lB << "comparing " << A[i] << " to " << B[i] << endl;
     if (i >= lB) return false;
     if (A.data[i] < B.data[i]) return true;
     else if (A.data[i] > B.data[i]) return false;
   }
   return false;
 }
};



class Relation
{
public:
 vector<string> columns;
 set<Tuple, tupleCompare> tuples;
 Relation(vector<string> col_names);
 Relation select(vector<Constraint>& constraints);
 Relation project(vector<int>& newInds);
 Relation rename(vector<string> newNames);
 void add(vector<string> v);
 void add(Tuple t);
 int size();
 string toString();
};

string tuple_to_string(vector<string>& t);
string named_tuple_to_string(vector<string>& t, vector<string>& names);


#endif
