#include "graphs/shortest_path_algorithms.hpp"

int smallest(int vertexNum, std::vector<int> path, ShortestPathResult result)
{
    int smallest = -1;
    int cost = INFI;
    int flag = 0;

    for(int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < path.size(); j++)
        {
            if(path[j] == i)
            {
                flag = 1;
                break;
            } 
        }
        if(result[i].cost < cost && flag == 0)
        {
            smallest = i;
            cost = result[i].cost;
        }
        flag = 0;
    }
    return smallest;
}

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    for (int i = 0; i < graph.vertexNum; i++)
    {
        result[i].cost = INFI;
    }
    result[sourceIndex].cost = 0;

    std::vector<int> pathOfAlgorithm;
    pathOfAlgorithm.push_back(sourceIndex);

    for (int i = 0; i < graph.vertexNum - 1; i++)
    {
        int next;

        for (int j = 0; j < graph.getNumberOfIterations(pathOfAlgorithm[i]); j++)
        {
            if (graph.checkExistence(pathOfAlgorithm[i], graph.getIndex(pathOfAlgorithm[i], j)))
            {
                if (result[pathOfAlgorithm[i]].cost + graph.getCost(pathOfAlgorithm[i], j) < result[graph.getIndex(pathOfAlgorithm[i], j)].cost)
                {
                    result[graph.getIndex(pathOfAlgorithm[i], j)].cost = result[pathOfAlgorithm[i]].cost + graph.getCost(pathOfAlgorithm[i], j);
                    result[graph.getIndex(pathOfAlgorithm[i], j)].path = result[pathOfAlgorithm[i]].path;
                    result[graph.getIndex(pathOfAlgorithm[i], j)].path.push_back(pathOfAlgorithm[i]);
                }
            }
        }

        if (i < graph.vertexNum - 2)
        {
            next = smallest(graph.vertexNum, pathOfAlgorithm, result);
            pathOfAlgorithm.push_back(next);
        }
    }

    for (int i = 0; i < graph.vertexNum; i++)
    {
        result[i].path.push_back(i);
    }
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    /* for (int i = 0; i < graph.vertexNum; i++)
    {
        result[i].cost = INFI;
    }
    result[sourceIndex].cost = 0;

    for (int k = 0; k < graph.vertexNum - 1; k++)
    {
        for (int i = 0; i < graph.vertexNum - 1; i++)
        {
            int next;

            for (int j = 0; j < graph.getNumberOfIterations(pathOfAlgorithm[i]); j++)
            {
                if (graph.checkExistence(pathOfAlgorithm[i], graph.getIndex(pathOfAlgorithm[i], j)))
                {
                    if (result[pathOfAlgorithm[i]].cost + graph.getCost(pathOfAlgorithm[i], j) < result[graph.getIndex(pathOfAlgorithm[i], j)].cost)
                    {
                        result[graph.getIndex(pathOfAlgorithm[i], j)].cost = result[pathOfAlgorithm[i]].cost + graph.getCost(pathOfAlgorithm[i], j);
                        result[graph.getIndex(pathOfAlgorithm[i], j)].path = result[pathOfAlgorithm[i]].path;
                        result[graph.getIndex(pathOfAlgorithm[i], j)].path.push_back(pathOfAlgorithm[i]);
                    }
                }
            }

            if (i < graph.vertexNum - 2)
            {
                next = smallest(graph.vertexNum, pathOfAlgorithm, result);
                pathOfAlgorithm.push_back(next);
            }
        }
    }

    for (int i = 0; i < graph.vertexNum; i++)
    {
        result[i].path.push_back(i);
    }*/
    
    return true;
}
