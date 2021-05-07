#include <iostream>
#include <sstream>
#include <string>
#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"
#include "graphs/shortest_path_algorithms.hpp"
#include <filesystem>
#include <fstream>

using namespace std::string_literals;

int main(int argc, char* argv[])
{
    std::ifstream inputStream{"10_100%.txt"};
    auto graph = AdjacencyMatrixGraph::createGraph(inputStream);

    ShortestPathResult result;

    int sourceIndex;
    inputStream >> sourceIndex;

    dijkstra(*graph, sourceIndex, result);
    

    return 0;
}
