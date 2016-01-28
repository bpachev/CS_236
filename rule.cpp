#include "rule.h"

void Rule::setResult(Predicate* pred)
{
  result = pred;
}

string Rule::toString()
{
  string res = result->toString();
  res += " :- ";
  for (unsigned int i=0; i < premises.size(); i++)
  {
    if (i) res += ",";
    res += premises[i]->toString();
  }
  return res;
}

void Rule::addPred(Predicate * pred)
{
  premises.push_back(pred);
}

Rule::~Rule()
{
  delete result;
  for (unsigned int i = 0; i < premises.size(); i++)
  {
    delete premises[i];
  }
}
