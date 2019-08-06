# Multithreaded sort
My implementations for multithreaded sorting in C++

## Introduction and technical specifications
I had an idea, about modifying existing sorting algorithms like Merge sort and Quicksort. The idea was to add multithreading, to make them faster. Time and space complexities aren't changed, but it's actually made them faster. But I think it's a good idea to show how much faster they became and benchmark them against their original implementations and other sorting algorithms like `std::sort` and parallel `boost::block_indirect_sort`.  

## How to use
Since I have used only C++11 things, headers should be quite cross-platform(Checked on Windows but should run on Mac and Linux).
So just include header to your source file and linker.

## Main idea
When I have looked on recursive call tree, I realized that I could replace some recursive calls by thread creation. 

### First try
The first attempt was to maintain a specific number of threads(e.g. 8), if the current number of threads is less than 8, then create 2 more threads instead of 2 recursive calls. And if 2 threads finished their work, then subtract 2 from the current number of threads(for thread count I have used `std::atomic` to prevent race conditions). But at some point in time, it could look like this. 
![First try](/Images/1.png)  
As you can see we have unfair load distribution, thread 1 need to sort 500 elements, thread 2 have created threads 3 and 4 and therefore just waiting for them to complete their work(before doing merge and memcopy) and each of threads 3 and 4 needs to sort 250 elements. In this case, we have 4 threads, but only 3 doing actual work.
 
### Second try
The second attempt was to create threads instead of recursive calls based on the depth of the recursive call tree. Basically 2<sup>depth</sup> is a number of active threads. For example, if we choose depth to be 2, the sort function will create 2 threads and will wait for them to finish, each thread will create 2 more threads and will wait for them to finish hence we have at most 4 active threads, that actually doing work. Each thread has received 250 elements to sort. Looks pretty much fair distribution. 
![Second try](/Images/2.png)  
For now, I think, it's the most optimal solution.  

## Benchmarks
Let's compare `Merge sort`, `Quicksort`, `std::sort`, `boost::block_indirect_sort` and my modifications of `Merge sort` and `Quicksort`. 
The test machine is my laptop:D
* Intel Core i7-7700HQ(4 cores, 8 threads)
* 16GB RAM
* Windows 10 1903  
* GCC 8.1.0 (without explicit optimizations)

For time measurement I will use `chrono` and it's `high_resolution_clock` in milliseconds.
Test arrays contain random numbers, each sorting function receives a copy of the same test array(to make a fair comparison).
  
### 1 Thread
<p align="center">
  <img src="/Images/Benchmark1.png">
</p>    

In single-threaded mode, additional checks(for the current depth) that I have added to multithreaded versions of Merge sort and Quicksort, hadn't really worsened runtime. As we can see, upon sorting array of random numbers, time complexity of Quicksort became O(n<sup>2</sup>).
  
### 2 Threads
<p align="center">
  <img src="/Images/Benchmark2.png">
</p>
  
In 2 threaded mode, one additional thread didn't really help to Quicksort. But 2 versions of multithreaded Merge sort finished their work 2 times faster.  

### 4 Threads
<p align="center">
  <img src="/Images/Benchmark4.png">
</p>
  
In 4 threaded mode, Quicksort became 2 times faster than it's original single-threaded implementation. Somehow the first version of multithreaded Merge sort didn't benefit from 2 additional threads and finished its work in the exact same time as if he had only 2 threads. On the other hand, optimal version of multithreaded Merge sort finished its wort close to 4 times faster than its original implementation.  

### 8 Threads
It's time to add `boost::block_indirect_sort`.
<p align="center">
  <img src="/Images/Benchmark8.png">
</p>

There is no much difference between 8 threads and 4 threads because my machine has only 4 real cores. But still, all multithreaded versions of sorting algorithms improved their sorting time by 20 to 30 percents. 

## Conclusion

From the last graph, we can see that optimal version of Merge sort working on 8 threads finishes its work almost 5 times faster than its original single-threaded implementation. Moreover, my implementation got very close to `boost::block_indirect_sort`(which is very fast) in terms of time that took to finish the work. Lastly, the time complexity is still O(n log n) and the space complexity is O(n).