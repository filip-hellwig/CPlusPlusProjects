#include <memory>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


int main()
{
    int vertexNum = 150;
    int edgeNum = vertexNum * (vertexNum-1);
    std::ofstream MyFile("150_25%.txt");
    int iter = 0;

    MyFile << vertexNum << " " << edgeNum << std::endl;

    srand((unsigned) time(0));

    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum/4; j++)
        {
            if (i != iter)
            {
                MyFile << i << " " << iter++ << " " << (rand() % 100) + 1 << std::endl;
            } else
            {
                iter++;
            }
            iter = iter%vertexNum;
        }
    }

    MyFile << (rand() % vertexNum);

    MyFile.close();
};