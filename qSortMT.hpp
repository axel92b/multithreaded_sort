#pragma once
#include <thread>

//C++11
template<class T>
void quickSortAuxMT(T* a, int size, int maxDepth, int curDepth) {
  int p, left = 1, right = size - 1;
  if (size < 2)
    return;
  //partition
  std::swap(a[0], a[size / 2]);
  p = a[0];
  while (left <= right) {
    while (right >= left && a[right] >= p)
      right--;
    while (left <= right && a[left] < p)
      left++;
    if (left < right)
      std::swap(a[left++], a[right--]);
  }
  std::swap(a[0], a[right]);
  //end of partition
  if (curDepth <= maxDepth) {
    std::thread t(quickSortAuxMT<T>, a, right, maxDepth, curDepth + 1);
    std::thread t2(quickSortAuxMT<T>, a + right + 1, size - right - 1, maxDepth, curDepth + 1);
    t.join();
    t2.join();
  } else {
    quickSortAuxMT(a, right, maxDepth, curDepth + 1);
    quickSortAuxMT(a + right + 1, size - right - 1, maxDepth, curDepth + 1);
  }
}

//2^max_depth = number of working threads.
//If current depth <= max_depth for each recursive call will be created new thread.
//For example if max_depth = 3, then there will be 8 threads working on sorting.
template<class T>
void quickSortMT(T* arr, int size, int depth) {
  quickSortAuxMT(arr, size, depth, 1);
}
