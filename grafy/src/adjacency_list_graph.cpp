#include "graphs/adjacency_list_graph.hpp"

std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    AdjacencyListGraph resultGraph;
    std::vector<std::vector<graphConnection>> graph;
    int vertexNum, edgeNum;

    std::string line;
    std::getline(is, line, ' ');
    vertexNum = std::stoi(line);
    line.clear();

    std::getline(is, line);
    edgeNum = std::stoi(line);
    line.clear();

    for (int i = 0; i < vertexNum; i++) {

        std::vector<graphConnection> v1;
        graph.push_back(v1);
    }

    int firstVertex;
    graphConnection element;

    for(int i = 0; i<edgeNum; i++)
    {
        std::getline(is, line, ' ');
        firstVertex = std::stoi(line);
        line.clear();

        std::getline(is, line, ' ');
        element.endVertexIndex = std::stoi(line);
        line.clear();

        std::getline(is, line);
        element.cost = std::stoi(line);
        line.clear();

        graph[firstVertex].push_back(element);
    }

    /* resultGraph.graph = graph;
    resultGraph.vertexNum = vertexNum; */

    return std::make_unique<AdjacencyListGraph>(/* resultGraph */);
}
