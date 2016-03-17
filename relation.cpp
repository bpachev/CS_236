#include "relation.h"


Relation::Relation(vector<string> col_names)
{
  columns = col_names;
}

void Relation::unionWith(Relation& other, ostream& out)
{
   for (auto t: other.tuples)
   {
     if (tuples.find(t) == tuples.end()) out << "  " << t.namedToString(columns) << endl;
     add(t);
   }
}


void init_join_map(int * join_map, vector<string>& columns, vector<string>& ocols, vector<string>& new_names)
{
  size_t n_othercols = ocols.size();
  size_t ncols = columns.size();
  for (size_t i = 0; i < n_othercols; i++)
  {
    join_map[i] = -1;
    for (size_t j = 0; j < ncols; j++)
    {
      //If one column name is the same as another
      if (columns[j] == ocols[i]) {
        join_map[i] = j;
        break; // don't need to look any further, as there are no duplicate column names in a single relation
      }
    }

    // if the current column in table other is not in the first table, add it to the new columns
    if (join_map[i] == -1)
    {
      new_names.push_back(ocols[i]);
    }
  }
}

//Join this relation with another relation, creating a new relation
//Step 1: Determine the column names
Relation Relation::join(Relation& other)
{
  //initialize the columns of the new relation to be those of the first table
  vector<string> new_names = columns;
  vector<string> ocols = other.columns;
  // if join_map[i] is -1, then column i from table other is not found in the first table
  // if join_map[i] = j >=0, then column i from table other is the same as column j in the first table.
  int join_map[other.columns.size()];
  init_join_map(join_map, columns, ocols, new_names);

  Relation res = Relation(new_names);

  for (auto t1: tuples)
  {
    for (auto t2: other.tuples)
    {
      vector<string> newData = t1.data;
      bool is_compat = true;
      for (int k  = 0; k < t2.size(); k++)
      {
        if (join_map[k] >= 0)
        {
          if (t2[k] != t1[join_map[k]])
          {
            is_compat = false;
            break;
          }
        }
        else newData.push_back(t2[k]);
      }
      if (is_compat) res.add(Tuple(newData));
    }
  }

  return res;
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

Relation Relation::project(vector<string> names)
{
  vector<int> newCols;
  for (size_t k = 0; k < names.size(); k++)
  {
    for (size_t j = 0; j < columns.size(); j++) {
      if (names[k] == columns[j])
      {
        newCols.push_back(j);
        break;
      }
    }
  }
  // cout << "Projecting onto cols ";
  // for (size_t i=0; i < newCols.size(); i++) cout << newCols[i] << " ";
  // cout << endl;

  return project(newCols);
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
 for (size_t j = 0; j < t.size(); j++)
 {
  if (j)  res += " ";
  res += t[j];
 }
 return res;
}

string named_tuple_to_string(vector<string>& t, vector<string>& names)
{
 string res = "";
 for (size_t j = 0; j < t.size(); j++)
 {
  if (j)  res += " ";
  res += names[j];
  res += "=";
  res += t[j];
 }
 return res;
}
