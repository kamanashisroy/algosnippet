
Given a rod of length `n`, and the price p[n] of different size, We need to find the optimized way to cut that rod so that we can maximise our profit.

#### Dynamic programming in top-down-memoization way

The top-down divides the problem into subproblem,

```C++
// ...
for(i = from+1; i < n; i++)
	max = getMax(max, find_max_benefit_subproblem(n, prices, localMaxes, i) + prices[i-from-1]);
```

#### Dynamic programming in bottom-up-tabulation way

Bottom-up solution builds the table by iteration.

```C++
localMaxes[0] = prices[0];
for(int i=1; i < n; i++) {
	int max = prices[i];
	for(int j = 1; j < i; j++)
		max = getMax(max, localMaxes[i-j-1]+prices[j]);
	localMaxes[i] = max;
}
```
