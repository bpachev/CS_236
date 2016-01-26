#include "predicate.h"

string Predicate::toString()
{
  string res = name;
  res += "(";
  for (int i = 0; i < params.size(); i++)
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
  for (int i = 0; i < params.size(); i++)
  {
    delete params[i];
  }
}
