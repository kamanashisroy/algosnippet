
Floyd-Warshall (All node shortest path) algorithm
===========================================

Algorithm for all  node shortest path is done by dynamic programming.

The following is the matrix for directed graph.

```
*	0	1	2	3	4	5	6	7	8	9	
0	0 	-	-	-	-	-	-	-	-	-	
1	-	0 	3*	8 	6 	-	8*	-	-	-	
2	-	3 	1 	9 	9 	-	5 	-	-	-	
3	-	8 	9 	0 	14 	-	4 	-	-	-	
4	-	6 	9 	14 	0 	-	14 	-	-	-	
5	-	-	-	-	-	0 	-	-	-	-	
6	-	8 	5 	4 	14 	-	0 	-	-	-	
7	-	-	-	-	-	-	-	0 	-	-	
8	-	-	-	-	-	-	-	-	0 	-	
9	-	-	-	-	-	-	-	-	-	0 	
```

Here is the one for undirected graph.
Notice it is optimized, it uses only the upper triangle.
```
*	0	1	2	3	4	5	6	7	8	9	
0	0 	-	-	-	-	-	-	-	-	-	
1	-	0 	3*	8 	6 	-	8*	-	-	-	
2	-	3 	1 	9 	9 	-	5 	-	-	-	
3	-	8 	-	0 	14 	-	4 	-	-	-	
4	-	6 	-	-	0 	-	14 	-	-	-	
5	-	-	-	-	-	0 	-	-	-	-	
6	-	-	5 	4 	-	-	0 	-	-	-	
7	-	-	-	-	-	-	-	0 	-	-	
8	-	-	-	-	-	-	-	-	0 	-	
9	-	-	-	-	-	-	-	-	-	0 	
```


