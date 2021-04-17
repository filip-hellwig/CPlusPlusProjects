#include "sorting/sorting.hpp"

void Merge(std::vector<int> tab1, std::vector<int> tab2, std::vector<int>& tab_out)
{
    int size1 = tab1.size();
    int size2 = tab2.size();

    int i = 0;
    int j = 0;
    int k = 0;

    while(i < size1 && j < size2)
    {
        if(tab2[j] < tab1[i])
        {
            tab_out[k] = tab2[j];
            j++;
        } else
        {
            tab_out[k] = tab1[i];
            i++;
        }
        k++;
    }
    while(j < size2)
    {
        tab_out[k] = tab2[j];
        j++;
        k++; 
    }
    while(i < size1)
    {
        tab_out[k] = tab1[i];
        i++;
        k++; 
    }
}

int Partition(std::vector<int>& tab, int start, int end)
{
    int j = start;
    int pivot = tab[end];

    for(int i = start; i < end; i++)
    {
        if(tab[i] <= pivot)
        {
            int temp = tab[j];
            tab[j] = tab[i];
            tab[i] = temp;
            j++;
        }
    }
    int temp = tab[j];
    tab[j] = tab[end];
    tab[end] = temp;

    return j;
}


void bubbleSort(std::vector<int>& tab)
{
    for(int i = 0; i < tab.size()-1; i++)
    {
        for(int j=0, k=1; j < tab.size()-1; j++, k++)
        {
            if(tab[j] > tab[k])
            {
                int temp = tab[j];
                tab[j] = tab[k];
                tab[k] = temp;
            }
        }
    }
}

void insertSort(std::vector<int>& tab)
{
    // TODO: implement
}

void heapSort(std::vector<int>& tab)
{
    // TODO: implement
}

void quickSort(std::vector<int>& tab, int start, int end)
{
    if(start <= end)
    {
        int index = Partition(tab, start, end);

        quickSort(tab, start, index-1);
        quickSort(tab, index+1, end);
    }
}

void mergeSort(std::vector<int>& tab)
{
    std::vector<int> tab1;
    std::vector<int> tab2;
    int size = tab.size();

    if(size < 2)
    {
        return;
    }

    for(int i = 0; i < size/2; i++)
    {
        tab1.push_back(tab[i]);
    }
    for(int i = size/2; i < size; i++)
    {
        tab2.push_back(tab[i]);
    }
    mergeSort(tab1);
    mergeSort(tab2);
    Merge(tab1, tab2, tab);
}

void bucketSort(std::vector<int>& tab)
{
    // TODO: implement
}
