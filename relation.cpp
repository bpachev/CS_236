#include "relation.h"


Relation::Relation(vector<string> col_names)
{
  columns = col_names;
}


Relation Relation::select(vector<Constraint>& constraints)
{
  Relation res = Relation(columns);
  int l = constraints.size();

  for (int j = 0; j < tuples.size(); j++)
  {
   bool flag = true;
   for (int i = 0; i < l; i++)
   {
     if (!constraints[i].isMet(tuples[j]))
     {
       flag = false;
     }
   }

   if(flag) res.tuples.push_back(tuples[j]); // we know the entries will be traversed in sorted order
  }

  return res;
}

Relation Relation::project(vector<int>& newInds)
{
  int l = newInds.size();
  vector<string> newColumns;
  for (int k = 0; k < l; k++) newColumns.push_back(columns[newInds[k]]);
  Relation res = Relation(newColumns);
  for (int i=0; i < tuples.size(); i++)
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
 Relation res = Relation(newNames);
 for (int i=0; i < tuples.size(); i++)
 {
   res.tuples.push_back(tuples[i]);
 }
 return res;
}

int Relation::size()
{
  return tuples.size();
}

string Relation::toString()
{
 string res = "\n";
 for (int i = 0; i < tuples.size(); i++)
 {
   res += tuple_to_string(tuples[i]);
   res += "\n";
 }
 return res;
}

//utility function
string tuple_to_string(vector<string>& t)
{
 string res = "";
 for (int j = 0; j < t.size(); j++)
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

bool Constraint::isMet(vector<string>& tuple)
{
  if (ind > 0)
  {
    return (tuple[indexInTuple] == tuple[ind]);
  }
  else return (tuple[indexInTuple] == val);
}
