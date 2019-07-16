#include <cstring>
#include <thread>

//C++11
template<class T>
void merge(T a[], int sizeA, T b[], int sizeB, T c[]){
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

template<class T>
void mergeSortAuxMT(T* arr, T* temp, int size, int cur_depth, int max_depth){
  if (size < 2) {
    return;
  }
  int left = size/2;
  if (cur_depth <= max_depth) {
    std::thread t(mergeSortAuxMT<T>, arr, temp, left, cur_depth+1, max_depth);
    std::thread t1(mergeSortAuxMT<T>, (arr + left), temp, (size - left), cur_depth+1, max_depth);
    t.join();
    t1.join();
  } else {
    mergeSortAuxMT(arr, temp, left, cur_depth, max_depth);
    mergeSortAuxMT(arr + left, temp, (size - left), cur_depth, max_depth);
  }
  merge(arr,left,arr+left,size-left,temp);
  memcpy(arr, temp,size*sizeof(T));
}


//2^max_depth = number of working threads.
//If current depth <= max_depth for each recursive call will be created new thread.
//For example if max_depth = 3, then there will be 8 threads working on sorting.
template<class T>
void mergeSortMT(T arr[], int size, int max_depth = 3){
  T *temp = new T[size];
  int depth = 1;
  mergeSortAuxMT(arr, temp, size, depth, max_depth);
  delete[] temp;
}