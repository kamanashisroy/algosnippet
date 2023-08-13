
D-ary heap generalized multi-child heap
========================================

D-ary heap of order 1 is a binary heap.
If the order is 2 then the tree node has at most 4 children.
If the order is 3 then the tree node has at most 8 children.


#### Number of children vs number of comparison

Now when the number of children increases, the number of comparison increases while down-heap. So when comparison is costly higher order D-ary heap gets slower.

Note that relaxation in `Dijkstra algorithm` and the `heappop` operation is followed by down-heap.

#### Number of children vs number of swap

Again, when the number of children rises, there are less swap and the structure is more cache-coherent.

#### Handling duplicate elements

Note that comparing `less-than-equal` when checking the heap property reduces number of swap when the heap contains duplicate elements.

Problems
========

[Problem requiring pos](https://leetcode.com/contest/biweekly-contest-100/problems/find-score-of-an-array-after-marking-all-elements/)
