
Prim's Minimum Spanning Tree
=============================

All the following approaches use heap of heaps.

- Level-0 heaps are collections of edges in a tree-node.
- Level-1 heaps are min-heap of level-0 heaps.

```
               [adjucent-edge-list of node 2]
          [adjucent-edge-list of node 1]
  [adjucent-edge-list of node 0]

0 ------------------------ > Y (Edges sorted by weight)
```

But they uses different kinds of heaps as priority queues.


#### Binary Heap based

https://www.hackerrank.com/challenges/primsmstsub/submissions/code/85267461

#### Binomial Heap based

https://www.hackerrank.com/challenges/primsmstsub/submissions/code/85269706

#### D-ary heap based

https://www.hackerrank.com/challenges/primsmstsub/submissions/code/85270499

