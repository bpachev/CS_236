#include "graph.h"
#include <sstream>
#include <iostream>
#include <algorithm>

graph::graph()
{

}

graph::graph(int num_nodes)
{
  for (size_t i =0; i < num_nodes; i++) add_node();
}


graph graph::reverse()
{
  size_t nnodes = nodes.size();
  graph g = graph(nnodes);
  for (size_t i = 0; i < nnodes; i++)
  {
    int j;
    for (auto j: nodes[i].neighbors) g.add_edge(j,i);
  }

  return g;
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
    res << i << ":";
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

  temp_node_arr.push_back(node);
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

vector<int> graph::DFSForest(){
 temp_node_arr.clear();
 pos_num = 1;
 for (size_t i =0; i < nodes.size(); i++)
 {
   if (nodes[i].visited) continue;
   else explore(i);
 }
 return temp_node_arr;
}

//find strongly connected components of graph
vector<vector<int>> graph::SCC()
{
  size_t nnodes = nodes.size();
  graph g = reverse();
  vector<int> reverse_search_order = g.DFSForest();
  cout << endl << "Reversed Graph" << endl << g.toString() << endl << endl;
  vector<vector<int>> components;


  for (size_t i = 0; i < nnodes; i++)
  {
//    cout << reverse_search_order[i] << " ";
    int start_node = reverse_search_order[nnodes-i-1];
    if (nodes[start_node].visited) continue;
    temp_node_arr.clear();
    explore(start_node);
    sort(temp_node_arr.begin(), temp_node_arr.end());
    for (size_t k=0;k<temp_node_arr.size();k++) cout << temp_node_arr[k] << " ";
    cout << endl;
    components.push_back(temp_node_arr);
  }
  //cout << endl;
  return components;
}
