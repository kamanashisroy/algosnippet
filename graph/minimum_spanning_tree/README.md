
The generic greedy algorithm for finding minimum-spanning-tree is,

```
A = empty
while A does not form a spanning tree
	find an edge (u,v) that is safe for A
	A = A U {(u,v)}
return A
```



| Kruskal's algorithm | Prim's algorithm 
| --- | ---
| Iterates through each edges | Iterates through each vertices
| Maintains a minimum spanning forest in each iteration | Maintains one minimum spanning tree
| Uses disjoint set data structure.  | Uses priority queue(binary heap)
| Iterates through all the edges in non-decreasing order. | Iterates through all the vertices in a priority queue.
| `O(m*lg n)` which is actually the sorting complexity |  `O(m*lg n)`
