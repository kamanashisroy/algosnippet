
Insertion sort is fast when the input is small(arround 10, it depends on the machine).

It is still inversion-bound and comparison-based algorithm.

It can be optimized by a sorted state check. And it can be optimized using binary search.

In best case the running time is BigO(n). And on average it is BigO(n^2).

Insertion sort can be optimized by the idea of devide and conquer for example in merge sort.

Time complexity is `BigO(n*k)` for insertion sort when each element in the input is no more than k places away from its sorted position.

It is `online`. That means it works well for sequential data.
