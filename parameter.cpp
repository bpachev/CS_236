#include "parameter.h"

Parameter::Parameter()
{
  value = null;
  name = null;
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

String Parameter::toString()
{
  if (value == null) return name;
  else if (name == null) return value;
  return value;
}
