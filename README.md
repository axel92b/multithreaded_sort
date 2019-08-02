# Multithreaded sort
My implementations for multithreaded sorting in C++

## Introduction and technical specifications
I had an idea, about modifying existing sorting algorithms like Merge sort and Quick sort. The idea is to add multithreading, to make them faster. Time and space complexity aren't changed, but it's actually made them faster. But i think it's good idea to show how much faster they became and benchmark them against their original implementations(and std::sort).

## How to use
Since i have used only C++11 things, headers should be quite crossplatform(Checked on Windows, but should run on Mac and Linux).
So just include header to your source file and to linker.

## Main idea
When i have looked on recursive call tree, i realized that i can replace some recursive calls by thread creation. 

### First try
First attempt was to maintain specific number of threads(e.g. 8), if current number of threads is less than 8, then create 2 more threads instead of recursive calls. And if 2 Threads finished their work, then subtract 2 from current number of threads. But at some point of time it could look like this.  
![First try](/Images/1.png)  
As you can see we have unfair load distribution, Thread 1 need to sort 500 elements, Thread 2 have created Threads 3 and 4 and therefore just waiting for them to complete their work(before doing merge and memcopy) and Threads 3 and 4 need to sort 250 elements each. In this case we have 4 Threads, but only 3 doing actual work.
 
### Second try
Second attempt was to create threads instead of recursive calls based on depth of recursive call tree. Basically `2^depth` is number of active threads. For example if we choose depth to be 2, sort function will create 2 threads and will wait for them to finish, each thread will create 2 more threads and will wait for them to finish hence we have at most 4 active threads, that actually doing work. Each thread have received 250 elements to sort. Looks pretty much fair distribution.  
![Second](/Images/2.png)  
For now, i think, it's the most optimal solution.

## Benchmarks
Let's compare Merge sort, Quick sort, std::sort and my modifications of Merge sort and Quick sort.  
Test machine is my laptop:D
* Intel Core i7-7700HQ
* 16GB RAM
* Windows 10 1903  

For time measurement i will use `chrono` and it's `high_resolution_clock` in milliseconds.
Test array contains numbers in descending order.

### TODO

- [x] Uploaded first and most optimal version of multithreaded Merge sort(for now)
- [ ] Add info about implementation
- [ ] Compare original Merge sort, "naive" multithreaded Merge sort and my solution
- [ ] Multithreaded version of Quicksort
