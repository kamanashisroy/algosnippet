
Knapsack
============================


0-1 Knapsack bottomup
======================

0-1 Integer knapsack problem
============================

Integer knapsack can be solved by bottom-up dynamic programming in `O(C*n)` time, where the limit of the sack is `C`.

Here is the bottom-up dynamic programming table.

```
Badness Lims:	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,	16,	17,	18,	19,	
Max-Goodness:	0,	0,	0,	34,	0,	0,	45,	0,	0,	79,	0,	0,	83,	0,	0,	124,	0,	0,	128,	0,	
result = 128
successful 
```


It shows the different sizes/badness in the top row and the maximum value/goodness in the next.


Unbounded Integer Knapsack 
============================

Here is the output of the unbounded version of the same problem.

```
Badness Lims:	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,	16,	17,	18,	19,	
Max-Goodness:	0,	0,	0,	34,	0,	0,	68,	0,	0,	102,	0,	0,	136,	0,	0,	170,	0,	0,	204,	0,	
204
successful 
```



