
This is the dynamic implementation of 01Knapsack problem.

Subproblems
============

Each of the subproblem is divided into two subproblems. It has similarity with dynamic Fibonacci problem, where each of subproblem is divide into two as well.

```C++
	soln1 = find_optimal_subproblem(it, end, max_weight, db);
	if(item.second < max_weight) {
		soln2 = find_optimal_subproblem(it, end, max_weight - item.second, db);
		soln2.second += item.first;
		soln2.first.push_back(item);
	}
	soln_t ret = maxSoln(soln1, soln2);
```
But here it has added dimentionality of weight.

Time complexity
=====================

A recursive dynamic programming algorithm can be presented by subproblem graph. 

Subproblem graph consists of vertices resembling non-overlapping subproblems. And the directed edges in the vertex represent the recursive calls. The edges actually represent the dependency of the subproblems.

    The runtime of the dynamic algorithm = (time to solve each subproblem)*(number of unique subproblems)

Typically, 

    the cost = (outdegree of each vertex)*(number of vertices)

For knapsack, 

Outdegree of each vertex is at most 2=O(1). This is because in each subproblem, we try to solve it in at most two ways.

Now if we check the subproblems, we can find some pattern,

    The subproblem `(n,W)` depends on `(n-1,W)` and `(n-1,W-w(n))`.

    `(n-1,W)` depends on `(n-2,W)` and `(n-2,W-w(n-1))`
    `(n-1,W-w(n))` depends on `(n-2,W-w(n))` and `(n-2,W-w(n)-w(n-1))`


Note that for each of the `n` items, the weight can vary at most `1 to W`.
(We can compare this extended pattern with the dynamic Fibonacci problem pattern with added dimension.)

So there is at most `n*W` unique subproblems.

And as we solve each subproblem only once,

The running time = O(1)*O(n*W) = O(n*W).


