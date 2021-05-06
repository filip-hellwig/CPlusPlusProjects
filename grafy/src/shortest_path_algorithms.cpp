#include "graphs/shortest_path_algorithms.hpp"

int smallest(int vertexNum, std::vector<int> path, ShortestPathResult result)
{
    int smallest = -1;
    int cost = INFI;
    int flag = 0;

    for(int i = 0; i < vertexNum; i++)
    {   
        // Sprawdzamy czy dany wierzchołek był już wybrany
        // (Nie może być wybrany drugi raz)
        for (int j = 0; j < path.size(); j++)
        {   
            if(path[j] == i)
            {
                flag = 1;
                break;
            } 
        }

        // Jeżeli wierzchołek nie był jeszcze wybrany sprawdzamy
        // czy koszt połączenia do niego jest najmniejszy
        if(result[i].cost < cost && flag == 0)
        {
            smallest = i;
            cost = result[i].cost;
        }
        flag = 0;
    }

    return smallest;        // Zwracamy wierzchołek o najniżyszm koszcie połącznia 
}

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    // Inicjujemy tablicę wyników, koszta ustawiamy na INFI
    for (int i = 0; i < graph.vertexNum; i++)
    {
        result[i].cost = INFI;
    }
    // Koszt dotarcia do wierzchołka początkowego to 0
    result[sourceIndex].cost = 0;


    // Zmienna służąca do przechowywania drogi algorytmu
    // (Czyli przechowuje informacje o wszystkich poprzednich wierzchołkach)
    std::vector<int> pathOfAlgorithm;

    pathOfAlgorithm.push_back(sourceIndex);

    // Przechodzimy po wszystkich wierzchołkach oprócz ostatniego
    for (int i = 0; i < graph.vertexNum - 1; i++)
    {   
        // Ostatni wierzchołek w ścieżce
        int startVertex = pathOfAlgorithm[i];

        // Sprawdzamy wszystkie połączenia dla danego wierzchołka początkowego 
        for (int j = 0; j < graph.getNumberOfIterations(startVertex); j++)
        {
            if (graph.checkExistence(startVertex, graph.getIndex(startVertex, j)))
            {
                // Sprawdzamy czy nowy sposób dotarcia do wierzchołka jest 
                // mniej kosztowyny od starego sposobu
                if (result[startVertex].cost + graph.getCost(startVertex, j) 
                    < result[graph.getIndex(startVertex, j)].cost)
                {
                    // Przypisujemy nowy koszt dotarcia do wierzchołka
                    result[graph.getIndex(startVertex, j)].cost = 
                        result[startVertex].cost + graph.getCost(startVertex, j);

                    // Przypisujemy drogę dotarcia do wierzchołka początkowego połącznia
                    result[graph.getIndex(startVertex, j)].path = result[startVertex].path;

                    // Dodajemy do drogi wierzchołek początkowy
                    result[graph.getIndex(startVertex, j)].path.push_back(startVertex);
                }
            }
        }

        // Dodajemy następny wierzchołek do którego pójdziemy
        if (i < graph.vertexNum - 2)
        {
            pathOfAlgorithm.push_back(smallest(graph.vertexNum, pathOfAlgorithm, result));
        }
    }

    // Dodajemy do drogi wierzchołek końcowy
    for (int i = 0; i < graph.vertexNum; i++)
    {
        result[i].path.push_back(i);
    }
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    // Inicjujemy tablicę wyników, koszta ustawiamy na INFI
    for (int i = 0; i < graph.vertexNum; i++)
    {
        result[i].cost = INFI;
    }

    // Koszt dotarcia do wierzchołka początkowego to 0
    result[sourceIndex].cost = 0;

    // Pętlę wyknujemy ilość razy zgodną z ilością wierzchołków
    // Ostatnie iteracja służy do sprawdzenia czy nie ma ujemnej pętli
    for (int k = 0; k < graph.vertexNum; k++)
    {
        // Wykonujemy normalnie relaksację
        if (k < graph.vertexNum - 1)
        {
            // Przechodzimy po wszystkich wierzchołkach
            for (int i = 0; i < graph.vertexNum; i++)
            {   
                // Sprawdzamy wszystkie połączenia dla danego wierzchołka początkowego
                for (int j = 0; j < graph.getNumberOfIterations(i); j++)
                {
                    if (graph.checkExistence(i, graph.getIndex(i, j)) && result[i].cost != INFI)
                    {
                        // Sprawdzamy czy nowy sposób dotarcia do wierzchołka jest 
                        // mniej kosztowyny od starego sposobu
                        if (result[i].cost + graph.getCost(i, j) < result[graph.getIndex(i, j)].cost)
                        {
                            // Przypisujemy nowy koszt dotarcia do wierzchołka
                            result[graph.getIndex(i, j)].cost = result[i].cost + graph.getCost(i, j);

                            // Przypisujemy drogę dotarcia do wierzchołka początkowego połącznia
                            result[graph.getIndex(i, j)].path = result[i].path;

                            // Dodajemy do drogi wierzchołek początkowy
                            result[graph.getIndex(i, j)].path.push_back(i);
                        }
                    }
                }
            }
        } else      // Sprawdzamy wystąpienie ujemnej pętli
        {
            for (int i = 0; i < graph.vertexNum; i++)
            {
                for (int j = 0; j < graph.getNumberOfIterations(i); j++)
                {
                    if (graph.checkExistence(i, graph.getIndex(i, j)))
                    {
                        // Jeżeli jakikolwiek wierzchołek zmieniał by koszt to zwracamy fałsz
                        // (Wsyzstkie wiechołki powinny mieć ostateczne wartości dla vertexNum-1)
                        if (result[i].cost + graph.getCost(i, j) < result[graph.getIndex(i, j)].cost)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    // Dodajemy do drogi wierzchołek końcowy
    for (int i = 0; i < graph.vertexNum; i++)
    {
        result[i].path.push_back(i);
    }
    
    return true;
}
