#include "graphs/adjacency_matrix_graph.hpp"

int AdjacencyMatrixGraph::getNumberOfIterations(int index)
{
    return vertexNum;       // Zwracamy liczbę wierzchołków
}

bool AdjacencyMatrixGraph::checkExistence(int firstIndex, int secondIndex)
{
    // Sprawdzamy czy dane połącznie istnieje (INFI oznacza że nie istnieje)
    if(graph[firstIndex][secondIndex] != INFI)
    {
        return true;
    } else
    {
        return false;
    }
}

int AdjacencyMatrixGraph::getCost(int firstIndex, int secondIndex)
{
    return graph[firstIndex][secondIndex];          // Zwracamy dany element macierzy
}

int AdjacencyMatrixGraph::getIndex(int firstIndex, int secondIndex)
{
    return secondIndex;
}

std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is)
{
    AdjacencyMatrixGraph resultGraph;           // To będziemy zwracać, posiada graph i vertexNum
    std::vector<std::vector<int>> graph;
    int vertexNum, edgeNum;
    int firstVertex, secondVertex;
    std::string line;
    
    // Pobieramy liczbę wierzchołków
    std::getline(is, line, ' ');
    vertexNum = std::stoi(line);
    line.clear();

    // Pobieramy liczbę krawędzi
    std::getline(is, line);
    edgeNum = std::stoi(line);
    line.clear();

    // Inicjujemy graf
    for (int i = 0; i < vertexNum; i++) {

        std::vector<int> v1;
        for (int j = 0; j < vertexNum; j++) {
            v1.push_back(INFI);
        }
        graph.push_back(v1);
    }

    // Za pomocą pętli pobieramy wszystkie połącznia występujące w grafie
    for(int i = 0; i<edgeNum; i++)
    {
        // Pobieramy wierzchołek początkowy połączenia
        std::getline(is, line, ' ');
        firstVertex = std::stoi(line);
        line.clear();

        // Pobieramy wierzchołek końcowy połączenia
        std::getline(is, line, ' ');
        secondVertex = std::stoi(line);
        line.clear();

        // Pobieramy koszt połączenia
        std::getline(is, line);
        graph[firstVertex][secondVertex] = std::stoi(line);     //Wpisujemy połacznei do grafu
        line.clear();
    }

    resultGraph.graph = graph;
    resultGraph.vertexNum = vertexNum;

    return std::make_unique<AdjacencyMatrixGraph>(resultGraph);
}
