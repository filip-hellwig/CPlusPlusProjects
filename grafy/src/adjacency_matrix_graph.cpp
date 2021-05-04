#include "graphs/adjacency_matrix_graph.hpp"

std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is)
{
    AdjacencyMatrixGraph resultGraph;
    std::vector<std::vector<int>> graph;
    int vertexNum, edgeNum;

    std::string line;
    
    std::getline(is, line, ' ');
    vertexNum = std::stoi(line);
    line.clear();

    std::getline(is, line);
    edgeNum = std::stoi(line);
    line.clear();

    for (int i = 0; i < vertexNum; i++) {

        std::vector<int> v1;
        for (int j = 0; j < vertexNum; j++) {
            v1.push_back(INFI);
        }
        graph.push_back(v1);
    }
    
    int firstVertex, secondVertex;

    for(int i = 0; i<edgeNum; i++)
    {
        std::getline(is, line, ' ');
        firstVertex = std::stoi(line);
        line.clear();

        std::getline(is, line, ' ');
        secondVertex = std::stoi(line);
        line.clear();

        std::getline(is, line);
        graph[firstVertex][secondVertex] = std::stoi(line);
        line.clear();
    }

    resultGraph.graph = graph;
    resultGraph.vertexNum = vertexNum;

    return std::make_unique<AdjacencyMatrixGraph>(resultGraph);
}
