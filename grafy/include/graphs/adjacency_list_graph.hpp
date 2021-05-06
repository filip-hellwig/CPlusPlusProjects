#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>

#include "graphs/graph.hpp"

class AdjacencyListGraph : public Graph
{

  public:
    // Zmienna przechowująca graf bazująca na liście
    std::vector<std::vector<graphConnection>> graph;


    // Funkcja tworząca graf na bazie listy
    // Dane są zczytywane z pliku
    static std::unique_ptr<Graph> createGraph(std::istream& is);
    
    int getNumberOfIterations(int index) override;
    bool checkExistence(int firstIndex, int secondIndex) override;
    int getCost(int firstIndex, int secondIndex) override;
    int getIndex(int firstIndex, int secondIndex) override;
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
