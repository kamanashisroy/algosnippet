
Divide and conquer
===================

The divide and conquer described here, uses recursion tree. And the recursion tree is of size 2^n. So it is not the best strategy for subset sum problem.

The subproblem is defined as,
```C++
// here index is increased in each recursion ..
find_set(n, sum, arr, index+1, marker)
// the sum is decreasing
find_set(n, sum-arr[index], arr, index+1, marker);
```
So in each iteration there are two possible recursion tree. 

Here the branching factor is 2 and in each case the height of the recursion tree is n, where n is the number of input. So in **worst case when the sum is not found**, the time complexity is O(2^n).

