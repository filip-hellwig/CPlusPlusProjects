#include "timer.hpp"

#include <cstdlib>
#include <ctime>
#include <thread>
#include <iostream>
#include "sorting/sorting.hpp"

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    std::vector<int> tab(100000);

    /* srand((unsigned) time(0));

    for(int i = 0; i < tab.size(); i++)
    {
        tab[i] = (rand() % 100) + 1;
    } */

    for(int i = 0; i < tab.size(); i++)
    {
        tab[i] = tab.size() - i;
    }

    Timer timer, timer2, timer3;

    timer.start();
    quickSort(tab, 0, tab.size()-1);
    timer.stop();

    std::cout << "Quick - Waited for " << timer.sInterval() << "s\n";

    /* timer2.start();
    mergeSort(tab);
    timer2.stop();

    std::cout << "Merge - Waited for " << timer2.sInterval() << "s\n";

    timer3.start();
    bubbleSort(tab);
    timer3.stop();

    std::cout << "Bubble - Waited for " << timer3.sInterval() << "s\n"; */

    return 0;
}
