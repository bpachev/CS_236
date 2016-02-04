#include "relation.h"


Relation::Relation(vector<string> col_names)
{
  columns = col_names;
}

Relation::Relation(vector<Parameter>& params)
{
  for (int i = params; i < params.length(); i++)
  {
    columns.push_back(params[i].toString());
  }
}

Relation Relation::select(vector<Constraint>& constraints)
{
  Relation res = Relation(columns);
  int l = constraints.length();

  for (int j = 0; j < tuples.length(); j++)
  {
   bool flag = true;
   for (int i = 0; i < l; i++)
   {
     if (!constraints[i].isMet(tuples[j]))
     {
       flag = false;
     }
   }

   if(flag) res.tuples.push_back(entries[j]); // we know the entries will be traversed in sorted order
  }

  return res;
}

Relation Relation::project(vector<int> newInds)
{
  int l = newInds.length();
  res = Relation(newColumns);
  for (int i=0; i < tuples.length(); i++)
  {
    vector<string> newTuple;
    for (int j =0; j < l; j++)
    {
      newTuple.push_back(tuples[i][newInds[j]]);
    }
    res.tuples.push_back(newTuple);
  }

  return res;
}

Relation Relation::rename(vector<string> newNames)
{
 res = Relation(newNames);
 for (i=0; i < tuples.length(); i++)
 {
   res.tuples.push_back(tuples[i]);
 }
 return res;
}

int Relation::size()
{
  return tuples.length();
}

string Relation::toString()
{
 res = "\n";
 for (int i = 0; i < tuples.length(); i++)
 {
   res += tuple_to_string();
   res += "\n";
 }
 return res;
}

//utility function
string tuple_to_string(vector<string>& t)
{
 res = "";
 for (int j = 0; j < t.length(); j++)
 {
  res += t[j];
 }
 return res;
}

//constraint methods

Constraint::Constraint(int indexInTuple, int otherIndex)
{
 ind = otherIndex;
}

Constraint::Constraint(int indexInTuple,string value)
{
 val = value;
 ind = -1;
}

bool isMet(vector<string>& tuple)
{
  if (index > 0)
  {
    return (tuple[indexInTuple] == tuple[index]);
  }
  else return (tuple[indexInTuple] == val);
}
