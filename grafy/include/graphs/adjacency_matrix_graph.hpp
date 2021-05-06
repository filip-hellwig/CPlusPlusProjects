#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>

#include "graphs/graph.hpp"

class AdjacencyMatrixGraph : public Graph
{
  public:
    // Zmienna przechowująca graf bazujący na macierzy
    std::vector<std::vector<int>> graph;


    // Funkcja tworzy graf bazujący na macierzy
    // Dane są zczytywane z pliku
    static std::unique_ptr<Graph> createGraph(std::istream& is);

    int getNumberOfIterations(int index) override;
    bool checkExistence(int firstIndex, int secondIndex) override;
    int getCost(int firstIndex, int secondIndex) override;
    int getIndex(int firstIndex, int secondIndex) override;
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
