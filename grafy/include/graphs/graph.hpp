#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#define INFI 2147483646
#include <vector>
#include <iostream>
#include <map>
#include <utility>

struct graphConnection
{
    int endVertexIndex;
    int cost;
};

/* template<class T> */
class Graph
{
  public:
    std::vector<std::vector<int>> graph;
    int vertexNum;
};

/* template class Graph<int>;
template class Graph<graphConnection>; */

#endif /* GRAPH_HPP_ */
