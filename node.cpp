#include "node.h"

node::node()
{
  visited = false;
  pos_num = -1; //not initialized
}

void node::add(int other)
{
  neighbors.insert(other);
}
