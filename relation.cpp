#include "relation.h"


Relation::Relation(vector<string> col_names)
{
  columns = col_names;
}


Relation Relation::select(vector<Constraint>& constraints)
{
  Relation res = Relation(columns);
  int l = constraints.size();

  for (auto t: tuples)
  {
   bool flag = true;
   for (int i = 0; i < l; i++)
   {
     if (!constraints[i].isMet(t.data))
     {
       flag = false;
     }
   }

   if(flag) res.add(t); // we know the entries will be traversed in sorted order
  }

  return res;
}

Relation Relation::project(vector<int>& newInds)
{
  int l = newInds.size();
  vector<string> newColumns;
  for (int k = 0; k < l; k++) newColumns.push_back(columns[newInds[k]]);
  Relation res = Relation(newColumns);
  if (l <=0 ) return res;
  for (auto f : tuples)
  {
    vector<string> newTuple;
    for (int j =0; j < l; j++)
    {
      newTuple.push_back(f[newInds[j]]);
    }
    res.add(Tuple(newTuple));
  }

  return res;
}

Relation Relation::rename(vector<string> newNames)
{
 Relation res = Relation(newNames);
 for (auto t: tuples)
 {
   res.add(t);
 }
 return res;
}

void Relation::add(vector<string> v)
{
//  cout << "called add " << tuple_to_string(v) << endl;
  tuples.insert(Tuple(v));
}

string Relation::toString()
{
 string res = "";
 // res += tuple_to_string(columns);
 // res += "\n";
 for (auto t: tuples)
 {
   res += "  ";
   res += t.namedToString(columns);
   res += "\n";
 }
 return res;
}

void Relation::add(Tuple t)
{
  tuples.insert(t);
}

int Relation::size()
{
  return tuples.size();
}


//utility function
string tuple_to_string(vector<string>& t)
{
 string res = "";
 for (int j = 0; j < t.size(); j++)
 {
  if (j)  res += " ";
  res += t[j];
 }
 return res;
}

string named_tuple_to_string(vector<string>& t, vector<string>& names)
{
 string res = "";
 for (int j = 0; j < t.size(); j++)
 {
  if (j)  res += " ";
  res += names[j];
  res += "=";
  res += t[j];
 }
 return res;
}
