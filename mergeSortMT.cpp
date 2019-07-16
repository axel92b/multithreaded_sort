#include "mergeSortMT.hpp"


//C++11
void merge(int a[], int sizeA, int b[], int sizeB, int c[]){
  int ia = 0, ib = 0, ic = 0;
  while (ia < sizeA && ib < sizeB){
    if (a[ia] <= b[ib]){
      c[ic] = a[ia];
      ia++;
    }
    else{
      c[ic] = b[ib];
      ib++;
    }
    ic++;
  }
  while (ia < sizeA){
    c[ic] = a[ia];
    ic++;
    ia++;
  }
  while (ib < sizeB){
    c[ic] = b[ib];
    ic++;
    ib++;
  }
}

void mergeSortAuxMT(int* arr, int* temp, int size, int cur_depth, int max_depth){
  if (size < 2) {
    return;
  }
  int left = size/2;
  if (cur_depth <= max_depth) {
    std::thread t(mergeSortAuxMT, arr, temp, left, cur_depth+1, max_depth);
    std::thread t1(mergeSortAuxMT, (arr + left), temp, (size - left), cur_depth+1, max_depth);
    t.join();
    t1.join();
  } else {
    mergeSortAuxMT(arr, temp, left, cur_depth, max_depth);
    mergeSortAuxMT(arr + left, temp, (size - left), cur_depth, max_depth);
  }
  merge(arr,left,arr+left,size-left,temp);
  memcpy(arr, temp,size*sizeof(int));
}

void mergeSortMT(int arr[], int size, int max_depth){
  int *temp = new int[size];
  int depth = 1;
  mergeSortAuxMT(arr, temp, size, depth, max_depth);
  delete[] temp;
}