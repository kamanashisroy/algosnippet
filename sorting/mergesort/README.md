
Merge sort uses divide and conquer technique to optimize the sorting. It is simiar to insertion sort where instead of `BigO(n)` levels of insertions in insertion sort, merge sort takes `BigO(n)` levels of merge operations. But contrary to insertion sort, it is not inversion bound. 

The average runtime for merge sort is `BigO(n*log n)`. It is the same for best and average case.

Merge sort can be implemented using recursion or bottom up iteration. Refer to [CXX implementation](cxx).

Merge sort can be parallelized. 

TODO describe the memory concerns.
