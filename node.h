#ifndef NODE_H
#define NODE_H
#include <set>

using namespace std;
class node
{
public:
  set<int> neighbors;
  bool visited;
  int pos_num;

  node();
  void add(int other);
};

#endif
