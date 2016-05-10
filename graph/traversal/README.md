
Popular graph traversal algorithms are

- [Breadth-first search(BFS)](bfs)
- [Depth-first search(DFS)](dfs)


| Algorithm | Data-structure used | Unexplored | Discovered | Finished | Properties | Output | Running time | Use
| --- | --- | --- | --- | --- | --- | --- | --- | ---
| Breadth-fist search | Queue | | calculate distance(u.d) and precedence tree | u.f | generates minimum-spanning-tree. | breadth-first **tree**. | `O(|V| + |E|)` | Dijkstra and Prim's algorithms use similar technique. Checking bipartate graph.
| Depth-first search | Stack | for(v:V) {..} | calculate distance(u.d) | u.f < ancesotor.f | It finishes the deepest node first. It has backtracking | depth-first **forest**. | `Theta(|V| + |E|)` | In topological sort.

Breadh-first search is used in shortest path search in directed or undirected unweighted graph and minimum spanning tree. Depending of the starting node, breadth-first tree may varry but the distance from one node to another is always the same.

Depth-first search gives valuable information about the graph. It can give preordering(polish notation), postordering(reverse polish notation) and reversed postordering(used in topological sorting).

DFS is useful to find the common ancestor. A node u is ancestor of v if and only if v is first explored when u is marked explored but not finished.

DFS is useful to find the cycle in directed graph. A directed graph is acyclic if and only if depth-first search yelds no black edges.

DFS is useful to find cycle in undirected graph as well, it takes O(|V|) to do that.

DFS theorems and corollary
- Parenthesis theorem
- Nesting of descendant's intervals 
- White path theorem

Links
------

- [Iterative depth-first search](http://stackoverflow.com/questions/28879510/how-do-i-add-finishing-times-for-iterative-depth-first-search)
