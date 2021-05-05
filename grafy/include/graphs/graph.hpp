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

class Graph
{
  public:
    int vertexNum;

    virtual int getNumberOfIterations(int index) = 0;
    virtual bool checkExistence(int firstIndex, int secondIndex) = 0;
    virtual int getCost(int firstIndex, int secondIndex) = 0;
    virtual int getIndex(int firstIndex, int secondIndex) = 0;
};


#endif /* GRAPH_HPP_ */
