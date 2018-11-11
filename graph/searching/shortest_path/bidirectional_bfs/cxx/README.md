
The difference between the BFS(breadth-first search) and Dijstra-shortest path algorithm is the relaxation.

The pawn-move distance is monotonic function and hence it is suitable to use BFS.

The queen-move distance is non-monotonic function when a node is just explored, thus it requires relaxation . Dijkstra's shortest path algorithm is more suitable in this case.

```
S X G
1 X 1
1 2 1
```

Note that in the above queen move example, start `S` and goal `G` expand at the same time in bidirectional search. Node at row 2(row starting at 0 ending at n), col 0, we can reach there in multiple rook-moves. But the first move costs less than the next moves. So we should update the cost only when it is less than current cost in the way of relaxation.

**The BFS ends when we explore the goal node. The Dijkstra's shortest path algorithm ends when we pop() goal node from the queue.**

Finally I did it with bidirectional-Dijkstra . I am not sure if it is faster than normal Dijkstra though. I guess in cases bidirectional-Dijkstra algorithm may expand more nodes than normal Dijkstra algorithm.

Links
========

- [Castle on the grid](https://www.hackerrank.com/challenges/castle-on-the-grid/)
- [Bidirectional Dijkstra](https://cs.stackexchange.com/questions/57199/bidirectional-dijkstra-vs-dijkstra)
