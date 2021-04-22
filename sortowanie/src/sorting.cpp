#include "sorting/sorting.hpp"

/* Funkcja służy do łączenia oraz sortowania dwóch tablic */
void Merge(std::vector<int> tab1, std::vector<int> tab2, std::vector<int>& tab_out)
{
    int size1 = tab1.size();
    int size2 = tab2.size();

    int i = 0;          // Zmienne służące do iterowania po programie
    int j = 0;
    int k = 0;          

    /*
    Tutaj następuje sortowanie, wstawiamy wszystkie elementy tablicy nr2, które są mniejsze od danego elementu tablicy nr1
    */
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
    while(j < size2)            // Jeżeli skonczą nam się wszystkie elementy tablicy nr1 to dodajemy wszystkie elementy tablicy nr2
    {
        tab_out[k] = tab2[j];
        j++;
        k++; 
    }
    while(i < size1)            // Jeżeli skonczą nam się wszystkie elementy tablicy nr2 to dodajemy wszystkie elementy tablicy nr1
    {
        tab_out[k] = tab1[i];
        i++;
        k++; 
    }
}


// Funkcja służy do dzielenia dużej tablicy na teoretyczne, mniejsze tablice. Operujemy cały czas na jednej tablicy.
int Partition(std::vector<int>& tab, int start, int end)
{
    int j = start;          // Indeks początku sortowanej części tablicy
    int pivot = tab[end];           // Pivot jest ostatnim elementem naszej tablicy

    for(int i = start; i < end; i++)        // i wędruje po tabliy
    {
        if(tab[i] <= pivot)     // Jeżeli wartość tab[i] jest mniejsza od pivota to zamieniamy ją z tab[j]
        {
            int temp = tab[j];
            tab[j] = tab[i];
            tab[i] = temp;
            j++;            // W takim przypadku zwiększamy też j
        }
    }
    int temp = tab[j];          // Na koniec zamieniamy wartość tab[j] z tab[end]
    tab[j] = tab[end];
    tab[end] = temp;

    return j;
}


void bubbleSort(std::vector<int>& tab)      
{
    for(int i = 0; i < tab.size()-1; i++)           // Przechodzimy po tablicy n-1 razy i zamienieamy sąsiednie elementy
    {
        for(int j=0, k=1; j < tab.size()-1; j++, k++)
        {
            if(tab[j] > tab[k])         // Zamieniamy elementy
            {
                int temp = tab[j];
                tab[j] = tab[k];
                tab[k] = temp;
            }
        }
    }
}

void quickSort(std::vector<int>& tab, int start, int end)
{
    if(start <= end)        // Krok postawowy, część tablicy już posortowana
    {
        int index = Partition(tab, start, end);         // Sortujemy tablicę i dzielimy na podtablice

        quickSort(tab, start, index-1);         // Sortujemy podtablicę nr 1
        quickSort(tab, index+1, end);           // Sortujemy podtablicę nr 2
    }
}

void mergeSort(std::vector<int>& tab)
{
    std::vector<int> tab1;
    std::vector<int> tab2;
    int size = tab.size();

    if(size < 2)        // Krok podstawowy, tablica jednoelementowa
    {
        return;
    }

    for(int i = 0; i < size/2; i++)         // Podział głównej tablicy na dwie mniejsze
    {
        tab1.push_back(tab[i]);
    }
    for(int i = size/2; i < size; i++)
    {
        tab2.push_back(tab[i]);
    }

    mergeSort(tab1);            // Sortowanie mniejszych tablic
    mergeSort(tab2);
    Merge(tab1, tab2, tab);         // Złączanie mniejszych tablic w wejściową
}

