#include "parameter.h"

Parameter::Parameter(string v)
{
  value = v;
  name = "";
}

Parameter::Parameter(tok t)
{
  if (t.t == ID)
  {
    name = t.s;
  }
  else if (t.t == STRING)
  {
    value = t.t;
  }
}

string Parameter::toString()
{
  if (value == "") return name;
  else if (name == "") return value;
  return value;
}
