
Subset sum has different variations. And they fall into decision problem domain and optimization problem domain.

- Given a set of integers, is there a non-empty subset whose sum is K?(decision problem)
- [Given a set of integers, find all the subset whose sum is K.](dinamic/)
- [Given a set of integers, is there a non-empty subset whose sum is K, where the integers can repeat any number of times.](repeatsum)
- [Given a set of integers, divide the set into two set, S1 and S2, such that, the sum of S1 is equal to the sum of S2.](partitionsum)

There are many ways to solve subset sum problem.

- [Divide and conquer](divide_and_conquer/)
- [Dinamic programming](dinamic/)

If the subset-sum problem is designed for k elements where k = 2, the problem statements is like the following,

"Given n integers, determine a pair of numbers whose sum is x"
- [We can do it by divide and conquer](pairsum_by_divide/), It takes `BigO(n*log n)` time.
- [We can do it by distribution(counting)](pairsum_by_counting/), It takes `BigO(n)` time.
