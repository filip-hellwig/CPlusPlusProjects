#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#define INFI 2147483646
#include <vector>
#include <iostream>
#include <map>
#include <utility>

// Struktura służąca do implementacji grafu na liście
struct graphConnection
{
    int endVertexIndex;     // Wierchołek do którego prowadzi połączenie
    int cost;               // Koszt połączenia
};

class Graph
{
  public:
    // Zmienna przechowująca liczbę wierzchołków grafu
    int vertexNum;


    // Funkcja zwraca liczbę iteracji, które mają się wykonać w pętli
    virtual int getNumberOfIterations(int index) = 0;

    // Funkcja sprawda czy dane połączenie istnieje
    virtual bool checkExistence(int firstIndex, int secondIndex) = 0;

    // Funkcja zwraca koszt połącznia
    virtual int getCost(int firstIndex, int secondIndex) = 0;

    // Funkcja zwraca wierzchołek do którego prowadzi połącznie
    virtual int getIndex(int firstIndex, int secondIndex) = 0;
};


#endif /* GRAPH_HPP_ */
