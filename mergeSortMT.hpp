#include <cstring>
#include <thread>

//C++11
void merge(int a[], int sizeA, int b[], int sizeB, int c[]);
void mergeSortAuxMT(int* arr, int* temp, int size, int cur_depth, int max_depth);
void mergeSortMT(int arr[], int size, int max_depth);