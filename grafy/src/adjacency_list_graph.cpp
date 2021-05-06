#include "graphs/adjacency_list_graph.hpp"

int AdjacencyListGraph::getNumberOfIterations(int index)
{
    return graph[index].size();         // Zwracamy ilość połączeń dla danego wierzchołka początkowego
}

bool AdjacencyListGraph::checkExistence(int firstIndex, int secondIndex)
{
    return true;            // Zawsze istnieje
}

int AdjacencyListGraph::getCost(int firstIndex, int secondIndex)
{
    return graph[firstIndex][secondIndex].cost;         // Pobieramy koszt połączenia z listy
}

int AdjacencyListGraph::getIndex(int firstIndex, int secondIndex)
{
    return graph[firstIndex][secondIndex].endVertexIndex;       // Pobieramy wierzchołek końcowy z listy
}


std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    AdjacencyListGraph resultGraph;         // Zmienna którą zwracamy, zawiera graph oraz vertexNum
    std::vector<std::vector<graphConnection>> graph;
    int vertexNum, edgeNum;
    int firstVertex;
    graphConnection element;
    std::string line;

    // Pobieramy liczbę wierzchołków
    std::getline(is, line, ' ');
    vertexNum = std::stoi(line);
    line.clear();

    // Pobieramy liczbę połączeń
    std::getline(is, line);
    edgeNum = std::stoi(line);
    line.clear();

    // Inicjujemy graf
    for (int i = 0; i < vertexNum; i++) {

        std::vector<graphConnection> v1;
        graph.push_back(v1);
    }   

    // Przy pomocy pętli pobieramy wszystkie połączenia występujące w grafie
    for(int i = 0; i<edgeNum; i++)
    {   
        // Pobieramy wierzchołek początkowy połączenia
        std::getline(is, line, ' ');
        firstVertex = std::stoi(line);
        line.clear();

        // Pobieramy wierzchołek końcowy połączenia
        std::getline(is, line, ' ');
        element.endVertexIndex = std::stoi(line);
        line.clear();

        // Pobieramy koszt połączniea
        std::getline(is, line);
        element.cost = std::stoi(line);
        line.clear();

        // Wpisujemy połącznie do grafu
        graph[firstVertex].push_back(element);
    }

    resultGraph.graph = graph;
    resultGraph.vertexNum = vertexNum;

    return std::make_unique<AdjacencyListGraph>(resultGraph);
}
