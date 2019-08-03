#pragma once
#include <thread>
//C++11

//Declarations
/**
 * Generic multithreaded Quick sort.
 * @tparam T - Generic type argument.
 * @param arr - Array of elements.
 * @param size - Size of array.
 * @param max_depth - 2^max_depth determines number of threads
 *                (For example if max_depth = 3, then there will be 8 threads working on sorting.).
 */
template<class T>
void quickSortMT(T* arr, int size, int max_depth = 2);

//Auxiliary function
template<class T>
void quickSortAuxMT(T* arr, int size, int maxDepth, int curDepth);


//Definitions

template<class T>
void quickSortAuxMT(T* arr, int size, int maxDepth, int curDepth) {
  int p, left = 1, right = size - 1;
  if (size < 2)
    return;
  //partition
  std::swap(arr[0], arr[size / 2]);
  p = arr[0];
  while (left <= right) {
    while (right >= left && arr[right] >= p)
      right--;
    while (left <= right && arr[left] < p)
      left++;
    if (left < right)
      std::swap(arr[left++], arr[right--]);
  }
  std::swap(arr[0], arr[right]);
  //end of partition
  if (curDepth <= maxDepth) {
    std::thread t(quickSortAuxMT<T>, arr, right, maxDepth, curDepth + 1);
    std::thread t2(quickSortAuxMT<T>, arr + right + 1, size - right - 1, maxDepth, curDepth + 1);
    //wait for threads to finish
    t.join();
    t2.join();
  } else {
    quickSortAuxMT(arr, right, maxDepth, curDepth + 1);
    quickSortAuxMT(arr + right + 1, size - right - 1, maxDepth, curDepth + 1);
  }
}


template<class T>
void quickSortMT(T* arr, int size, int max_depth) {
  quickSortAuxMT(arr, size, max_depth, 1);
}
