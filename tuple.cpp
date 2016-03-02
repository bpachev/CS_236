#include "tuple.h"

Tuple::Tuple(vector<string>& v)
{
  data = v;
}

string Tuple::toString()
{
  return "";
}

string Tuple::namedToString(vector<string>& names)
{
  string res = "";
  for (size_t j = 0; j < data.size(); j++)
  {
   if (j)  res += " ";
   res += names[j];
   res += "=";
   res += data[j];
  }
  return res;
}

int Tuple::size()
{
  return data.size();
}

string& Tuple::operator[](int indx)
{
  return data[indx];
}
