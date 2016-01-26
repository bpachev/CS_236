#include "rule.h"

string Rule::toString()
{
  string res = result->toString();
  res += " :- ";
  for (int i=0; i < premises.size(); i++)
  {
    if (i) res += ",";
    res += premises[i]->toString();
  }
}

void Rule::addPred(Predicate * pred)
{
  premises.push_back(pred);
}

Rule::~Rule()
{
  delete result;
  for (int i = 0; i < premises.size(); i++)
  {
    delete premises[i];
  }
}
