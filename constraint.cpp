#include "constraint.h"
#include <sstream>
//constraint methods

Constraint::Constraint(int indexInTuple, int otherIndex)
{
 this->indexInTuple = indexInTuple;
 ind = otherIndex;
 val = "";
}

Constraint::Constraint(int indexInTuple,string value)
{
 this->indexInTuple = indexInTuple;
 val = value;
 ind = -1;
}

bool Constraint::isMet(vector<string>& tuple)
{
  if (ind >= 0)
  {
    return (tuple[indexInTuple] == tuple[ind]);
  }
  else return (tuple[indexInTuple] == val);
}

string Constraint::toString()
{
  stringstream s;
  s << "ind in tuple " << indexInTuple << " " << ind << " val " << val;
  return s.str();
}
