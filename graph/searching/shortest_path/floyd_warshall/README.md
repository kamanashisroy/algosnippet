
Floyd Warshall algorithm works to find the shortest path from one point to all the other points. It does it by dynamic programming. It tries to find the optimal solution through all the possible points.

It does it in |V|^3 time complexity.

#### test input

The input files contain the number of nodes and number of edges. The last parameter is the root node identifier-number.The nodes are numbered by 0,1,2...n. 
5 8 0
It is followed by the directed edges and weights.
0 1 4
The line above means there is a directed edge from node 0 to node 1 of weight 4.
