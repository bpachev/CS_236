#include "graph.h"
#include <sstream>
#include <iostream>

graph::graph()
{

}

void graph::add_edge(int source, int dest) {
  nodes[source].add(dest);
}

void graph::add_node(){
  nodes.push_back(node());
}

string graph::toString()
{
  stringstream res;
  for (size_t i = 0; i < nodes.size(); i++)
  {
    res << i;
    int j;
    for (auto j: nodes[i].neighbors)
    {
      res << " " << j;
    }
    res << endl;
  }
  return res.str();
}

void graph::explore(int node)
{
  int other;
  nodes[node].visited = true;
  for (auto other: nodes[node].neighbors)
  {
    if (nodes[other].visited) continue;
    explore(other);
  }

  nodes[node].pos_num = pos_num;
  nums_to_nodes.push_back(node);
  pos_num++;
}

string graph::pos_nums()
{
  stringstream res;
  DFSForest();
  for (size_t i = 0; i< nodes.size(); i++)
  {
    res << i << " " << nodes[i].pos_num << endl;
  }
  return res.str();
}

void graph::DFSForest(){
 nums_to_nodes.clear();
 pos_num = 1;
 for (size_t i =0; i < nodes.size(); i++)
 {
   if (nodes[i].visited) continue;
   else explore(i);
 }
}
