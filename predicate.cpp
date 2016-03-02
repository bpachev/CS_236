#include "predicate.h"

Predicate::Predicate(string n)
{
  name = n;
}

vector<string> Predicate::paramNames()
{
 
}

string Predicate::toString()
{
  string res = name;
  res += "(";
  for (unsigned int i = 0; i < params.size(); i++)
  {
    if (i) res += ",";
    res += params[i]->toString();
  }
  res += ")";
  return res;
}

void Predicate::addParam(tok t)
{
  params.push_back(new Parameter(t));
}

Predicate::~Predicate()
{
  for (unsigned int i = 0; i < params.size(); i++)
  {
    delete params[i];
  }
}
