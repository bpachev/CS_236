#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include <vector>
#include <iostream>

class graph {
public:
  int pos_num;
  vector<node> nodes;
  vector<int> temp_node_arr;
  graph();
  graph(int num_nodes);
  graph reverse();
  void add_edge(int source, int dest);
  void add_node();
  vector<vector<int>> SCC();
  //return the indices of the nodes searched, in order of traversal
  vector<int> DFSForest();
  void explore(int node);
  string toString();
  string pos_nums();
};

#endif
