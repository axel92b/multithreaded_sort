#include <cstring>
#include <thread>

//C++11
void merge(int a[], int sizeA, int b[], int sizeB, int c[]);
void mergeSortAuxMT(int* arr, int* temp, int size, int cur_depth, int max_depth);
//2^max_depth = number of working threads.
//If current depth <= max_depth for each recursive call will be created new thread.
//For example is max_depth = 3, then there will be 8 threads working on sorting.
void mergeSortMT(int arr[], int size, int max_depth);