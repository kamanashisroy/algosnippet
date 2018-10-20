
Knapsack
============================

0-1 Knapsack bottomup
======================

0-1 Integer knapsack problem
============================

Integer knapsack can be solved by bottom-up dynamic programming in `O(C*n)` time, where the limit of the sack is `C`.

Here is the bottom-up dynamic programming table.

```
Badness Input:	  32,  56,   3,   6,  23,   6,   3,
Goodness Input:	  12,  23,  34,  45,  56,  32,   4,
Badness Lims:	Iter    0 ,   1 ,   2 ,   3 ,   4 ,   5 ,   6 ,   7 ,   8 ,   9 ,  10 ,  11 ,  12 ,  13 ,  14 ,  15 ,  16 ,  17 ,  18 ,  19 ,  20 ,
Max-Goodness:	   0,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,
Max-Goodness:	   1,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,
Max-Goodness:	   2,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,   0 ,
Max-Goodness:	   3,   0 ,   0 ,   0 ,  34 ,  34 ,  34*,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,  34 ,
Max-Goodness:	   4,   0 ,   0 ,   0 ,  34 ,  34 ,  34 ,  45 ,  45 ,  45 ,  79 ,  79 ,  79*,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,
Max-Goodness:	   5,   0 ,   0 ,   0 ,  34 ,  34 ,  34 ,  45 ,  45 ,  45 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 ,
Max-Goodness:	   6,   0 ,   0 ,   0 ,  34 ,  34 ,  34 ,  45 ,  45 ,  45 ,  79 ,  79 ,  79 ,  79 ,  79 ,  79 , 111 , 111 , 111*, 111 , 111 , 111 ,
Max-Goodness:	   7,   0 ,   0 ,   0 ,  34 ,  34 ,  34 ,  45 ,  45 ,  45 ,  79 ,  79 ,  79 ,  83 ,  83 ,  83 , 111 , 111 , 111 , 115 , 115 , 115*,
Selected items:(idx=7,bad=0,good=0)(idx=6,bad=3,good=4)(idx=4,bad=23,good=56)(idx=3,bad=6,good=45)
115
successful 
```


It shows the different sizes/badness in the top row and the maximum value/goodness in the next.


Unbounded Integer Knapsack 
============================

Here is the output of the unbounded version of the same problem.

```
Badness Input:	  32,  56,   3,   6,  23,   6,   3,
Goodness Input:	  12,  23,  34,  45,  56,  32,   4,
Badness Lims:	   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,
Max-Goodness:	   0,   0,   0,  34,  34,  34,  68,  68,  68, 102, 102, 102, 136, 136, 136, 170, 170, 170, 204, 204, 204,
204
successful 
```

Congruence approach and convex hull optimization
===================================================

TODO math.

Divide by GCD optimization
===========================

Dividing the input size(badness) of the sack and the limit with GCD may reduce the `C` by constant time.

Links
========

- [Explanatory video](https://www.youtube.com/watch?v=U4O3SwDamA4)
- [Skiena notes](http://algorist.com/problems/Knapsack_Problem.html)
- [Collection of algorithms for knapsack](http://hjemmesider.diku.dk/~pisinger/codes.html)

