
Bidireaction Breadth-first-search searches from both side. It is faster than Breadth-first-search in a sense that the search is like a rhombus rather than a triangle with fat(costly) bottom.

In terms of branching factor, b and the distance of the two ndoes, d, the bidirectional breadth-first search gives the time complexity of O(b^(d/2)) while the normal bfs gives O(b^d).
