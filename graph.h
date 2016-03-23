#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include <vector>
#include <iostream>

class graph {
public:
  int pos_num;
  vector<node> nodes;
  vector<int> nums_to_nodes;
  graph();
  void add_edge(int source, int dest);
  void add_node();
  void DFSForest();
  void explore(int node);
  string toString();
  string pos_nums();
};

#endif
