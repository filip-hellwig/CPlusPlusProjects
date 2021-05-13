#include <iostream>
#include <sstream>
#include <string>
#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"
#include "graphs/shortest_path_algorithms.hpp"
#include <filesystem>
#include <fstream>

#include "timer.hpp"
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace std::string_literals;
using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    std::ifstream inputStream{"../data/graph/125_100%.txt"};
    std::ofstream MyFile1;
    std::ofstream MyFile2;

    /* auto graph = AdjacencyMatrixGraph::createGraph(inputStream); */
    auto graph = AdjacencyListGraph::createGraph(inputStream);

    ShortestPathResult result, result2;
    Timer timer, timer2;

    int sourceIndex;

    inputStream >> sourceIndex;

    MyFile1.open("Result1.txt", std::ios_base::app);
    MyFile2.open("Result2.txt", std::ios_base::app);
 

    timer.start();
    dijkstra(*graph, sourceIndex, result);
    timer.stop();

    MyFile1 << timer.sInterval() << "\n";

    timer2.start();
    bellmanFord(*graph, sourceIndex, result2);
    timer2.stop();

    MyFile2 << timer2.sInterval() << "\n";

    MyFile1.close();
    MyFile2.close();

    return 0;
}
