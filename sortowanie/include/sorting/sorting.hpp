#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <vector>

void bubbleSort(std::vector<int>& tab);
void insertSort(std::vector<int>& tab);
void heapSort(std::vector<int>& tab);
void quickSort(std::vector<int>& tab, int start, int end);
void mergeSort(std::vector<int>& tab);
void bucketSort(std::vector<int>& tab);

#endif /* SORTING_HPP_ */
