#ifndef SHORTEST_PATH_ALGORITHMS_HPP_
#define SHORTEST_PATH_ALGORITHMS_HPP_

#include "graphs/graph.hpp"

#include <map>
#include <utility>
#include <vector>

// Struktura służąca do przechowywania kosztu i drogi związanej
// z dotarciem do dowolnego wierzchołka
struct VertexResult
{
    int cost;
    std::vector<int> path;
};

using ShortestPathResult = std::map<int, VertexResult>;

// Funkcja służąca do szukania następnego wierchołka do którego ma się udać algorytm
int smallest(int vertexNum, std::vector<int> path, ShortestPathResult result);

// Funkcja służąca do szukania wszystkich najmniejszych dróg prowadzących z wierzchołka początkowego
// do wszystkich pozostałych wierchołków za pomocą algorytmu Dijkstry
void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result);

// Funkcja służąca do szukania wszystkich najmniejszych dróg prowadzących z wierzchołka początkowego
// do wszystkich pozostałych wierchołków za pomocą algorytmu Bellmana-Forda
bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result);

#endif /* SHORTEST_PATH_ALGORITHMS_HPP_ */
