
In dfs the nodes have two stages. One is marking(on process) and another is finished. Note that it does not work when there is a cycle.

And dfs can be implemented using recursive form and it can be done using stack. But in **recursive form we can easily know the finishing time of the node**. Here this property is used to do topological sort. [Here is an iterative version](../../traversal/dfs).

Time complexity
=====================

The cost of topsort is Theta(|V| + |E|) .
