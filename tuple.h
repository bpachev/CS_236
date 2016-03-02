#ifndef TUPLE_H
#define TUPLE_H
#include <vector>
#include <string>
using namespace std;

class Tuple
{
public:
  vector<string> data;
  Tuple(vector<string>& v);
  string toString();
  string namedToString(vector<string> & names);
  int size();
  string& operator[](int indx);
};

#endif
