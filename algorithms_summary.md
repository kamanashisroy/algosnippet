Apart from strong will and creativity there are some approaches of problem solving. These approaches can be used when there is enough insight gained about the problem. 

Here I shall try to summarize the approaches we use to solve algorithmic problems. The most popular problem solving approaches in computer science are,

1. Brute force.
2. Partition based.
3. Distribution based.
4. Dynamic programming.
5. Greedy approach.
6. Backtracking.
7. Branch-and-bound
8. Randomized algorithms.
9. Transformation based.

In particular problem solving it is common to use multiple approaches.

Brute-force approach gives the insight of the algorithm and the possible ways of optimization. 

Partition-based, dynamic-programming and greedy-approach all work in sub-problems. Partition-based algorithms work when the sub-problems are not overlapping(exception is R-tree). 

Dynamic-programming works when the sub-problems are overlapping and when there is recalculation. It allows speedup by memoization or tabulation to avoid recalculation. In optimization problem dynamic programming works when the problem has optimal-subproblem characteristic, optimal solutions to the problem incorporates optimal solutions to the related subproblems. It runs in polynomial time when,
- the number of distinct subproblems involved is polynomial in the input size,
- and each subproblems are solved in polynomial time.

Greedy approach avoids some calculations. Both partition-based and greedy-approach (may be also backtracking) allow optimization based on decision tree pruning. 

| Approach | When applicable | Common feature | Examples
| --- | --- | --- | ---
| Partition-based | non-overlaping subproblems | data represented in tree or recursion tree or decision tree | Merge sort, Quick sort, [Binary search](graph/tree/bst) etc.
| Dynamic Programming | overlapping subproblems where there is recalculation and optimal solutions to the problem incorporates optimal solutions to the related subproblems(**optimal substructure characteristics**), that is the substructures are independent, that is **subproblem-graph is directed acyclic graph(DAG)** | recursion-memoization or iteration-tabulation in extra memory | Fast-fibonacci, and optimization problems like [Subset-sum problem](approaches/dynamic_programming/sum/subset_sum/), [Longest-common-substring problem](string/substring), [Rod-cutting problem](approaches/dynamic_programming/rodcutting), [Dijkstra algorithms](graph/shortest_path/dijkstra/) when updating the shortest path array.
| Greedy approach | Localy optimal solution can predict global optimal solution(optimal substructure characteristic). It is possible to make a choice of localy optimal solution. | sorting or finding the minimum and maximum | Fractional Knapsack, Subset-sum by sorting, [Kruskals minimum spanning tree algorithm](graph/minimum_spanning_tree/kruskal), [Dijkstra algorithms](shortest_path/dijkstra) when in subproblem, [activity selection problem](interval/activity_selection)
| Distribution based | When the range of data can fit into memory | sparse array for buckets and link-list for duplicates | Bucket-sort, Radix-sort, Hashtable
| Branch-and-bound | 
| Backtracking | multiple subproblems where some of them may not predict the expected result. | It has two phases, 1. when a subproblem in path is beging considered, 2. when a path is fully explored. | [Depth-first search](graph/traversal/dfs), [Eight-queen problem](graph/traversal/eight_queen_problem)

Distribution based algorithms can get speedup by parallel programming.

Again, some algorithms are implemented in incremental approach and some are implemented as recursion. And there are also different data-structure to represent, insert, delete, search, merge the data.

We have already studied different algorithms in our academy. Here I want to summarize and compare the algorithms to get valuable insights. Summary also helps identify their suitable application for the real world problem. 

There are two strategies of formulating a solution.

| Approach | When applicable | Common feature | Examples
| --- | --- | --- | ---
| top-down | | Recursion, Memoization(using map) | TODO
| bottom-up | | Iteration, Tabulation | TODO

In top-down approach we use abstraction to think less detailed. It is simple and natural to use recursion with top-down. In dynamic programming the recursion is normally used along with Memoization. In dynamic programming, top-down approach traverses the **subproblem-graph** like in depth-first traversal. The dependent subproblems are solved in their topological order. Note that if the subproblem-graph is not **directed acyclic graph(DAG)** then the dynamic programming cannot be applied. It is obvious because depth-first traversal is not complete(never ending) for DAG.

In bottom-up approach start from details and compose the final result from them. Normally the iterative solutions use bottom-up approach. In dynamic programming the bottom-up approach is normally used with tabulation. It is noted that in some problems the bottom-up-tabulation may result in computation of unnecessary subproblems than top-down-memoiazation. In dynamic programming, bottom-up approach traverses the **subproblem-graph** in topologically sorted order.

When both the top-down and bottom-up approaches have the same asymptotic running-time, the bottom-up-iterative approach often has much better constant factors than top-down-recursive approach.

The problem solving starts with input constraints. When a subproblem is being solved the constraints are being reduced. This is called **relaxation**.

For example, for sorting problem the constraints are `a[0] < a[1] < a[1] < .. < a[n]`. After every iteration of outer loop in bubble sort, the `a[i]..a[n]` elements are in final sorted position. That means those elements are out of the sort-constraint. The new constraint-set contains `a[0] < a[1] < a[2] .. < a[i]`. And thus in each iteration there is relaxation of constraints.

In the same way in Bellman-ford algorithm, after each iteration of outer loop, all paths from source to `u` has `i` or fiewer edges. So there are only `n-i` edges to be checked for shorter paths. So the shortest-path-constraints are being relaxed in each iteration. Actually it is relaxed in each update of dist[u] table.

Here is a mindmap to relate the different [problem solving approaches](mindmap/mindmap.dot).

![mindmap](https://cloud.githubusercontent.com/assets/973414/15445415/17623d9e-1eb3-11e6-9c9d-a97d59791845.png)

The algorithm problems can be categorized in the following domains. Like the algorithm approaches, these domains are not exclusive.

- Counting
- Sorting
- Searching
- Traversal
- State machine
- Optimization problem
- Decision problem
- Combinatorial problem
- Constraint satisfaction problem

The following table categorizes the popular problems into different domains.

| Domain | approaches and principles | Problem
| --- | --- | ---
| Counting | GCD algorithm, pegion-hole principle | LCM(Lowest-common-multiple) problem, graph coloring problem, Fibonacci number.
| Sorting | partition based approach, distribution based approach | [number sorting](sorting), augmented data sorting, [topological sorting](graph/topsort), string sorting(TODO give Theta(n) sorting algorithm for string, hint:radix tree)
| Searching | binary-search-tree, hash function, hashtable, trie | Searching in [binary search tree](graph/tree/bst), find median, finding overlaping pairs of a given pair, finding a point in a R tree, [finding substring](string/substring), suggesting word(TODO)
| Tree traversal | Backtracking | finding lowest common ancestor, finding subtree, [topological sort](graph/topsort), finding shortest path, finding hamiltonian cycle, TSP.
| State machine | Dynamic programming and backtracking | [Longest common substring](string/lcs), [finding substring](string/substring).
| Optimization problem | Dynamic programming and backtracking | [Subset-sum problem](approaches/dynamic_programming/sum/subset_sum), Knapsack problem, [Rod-cutting problem](approaches/dynamic_programming/rodcutting).
| Constraint Satisfaction problem | backtracking | [Eight queen problem](graph/traversal/eight_queen_problem), Map coloring problem
| Combinatorial problem | Dynamic programming, backtracking, approximation algorithm, bipartite graph | TSP, Minimum spanning tree,[Subset-sum problem](approaches/dynamic_programming/sum/subset_sum), Knapsack problem, Assignment problems

#### Sorting algorithms

Sorting algorithms can be categorized into inversion-bound, comparison-based, partition-based and distribution-based. 

![sorting venn diagram](sorting_venn.svg)

The Venn diagram above shows the popular sorting algorithms and their relation. 

Insertion-sort, bubble-sort and selection-sort are inversion-bound and they takes Big-Omega of (n^2) time on average.(todo link the proof) 

Again all inversion-bound algorithms are comparison based as well. All comparison based algorithms take at least Big-Omega of (n*log n) in worst case. 

Note that `partition-based` algorithms are `comparison-based` as well. As the name suggest `partition-based` algorithm reduces comparison by breaking the problem into **non-overlapping sub-problems**. Quick-sort, Heap-sort, Binary-tree-sort, Merge-sort are all `partition-based` algorithms. And like all the comparison based algorithms they take at least Big-Omega of (n*log n) in worst case.

Again, the sorting algorithms can be stable and unstable.

- stable
  - Merge sort
  - Insertion sort
  - Tim sort
  - Bubble sort
  - Library sort
- Unstable sort
  - Selection sort
  - Heap sort
  - in-place Quick sort
  - Intro sort

As we go deep into these algorithm we can find some similarity in them. 

![shorting algorithm similarity](sorting_algorithm_similarity.svg)

For example, heap-sort actually sorts by selecting the minimum or maximum value from the heap. So it has the same approach as selection sort. It is not practical to build heap with sequentially accessible data(linked list or tape drive). 

Merge sort does sorting by combine or merge operations. The combine operation has some similarity with insertion sort. Again merge sort can be optimized by using insertion sort in the small data. Merge sort is well suited for sequentially accessible data(linked list or tape drive) and it does not require binary tree. It takes O(n) extra memory which can be reduced in various ways(multi-way merge sort, alternating the memory to reduce memory copy). 

Like the Merge-sort, Quick-sort is partition based algorithm and it can be used alongside insertion sort. 

Insertion sort can be optimized by [binary search](graph/tree/bst).

Binary-tree-sort is also partition based algorithm that requires randomly-accessible memory(for example, array) to build tree and sequentially accessible memory(for example, linked-list) to handle duplicates. Note that it can be used to get unique elements from the given duplicates at O(n*log n) time. 

Finally, the bucket-sort, rank-sort, counter-sort are distribution based algorithm. And contrary to the algorithms we discussed earlier distribution based algorithms can sort data in O(n) time complexity. The parallel version of rank-sort can sort in O(n) time(while the sequential takes O(n^2)). The counter sort/histogram based algorithm can be used to check for duplicates at O(n) time. 

#### Searching algorithms

Searching algorithms take advantage of the sorted representation of the data. Popular searching algorithms are partition based. In particular they are tree based.

As discussed earlier, the tree representation generally needs randomly accessible memory to build the nodes and sequentially accessible memory to keep the duplicates.

| [Tree](graph/tree/tree) | Balanced binary tree | Data is represented | Type of data
| --- | --- | --- | ---
| Heap | not balanced | all nodes | Comparable
| AVL-tree | balanced | 
| [Red-black tree](graph/tree/rbtree) | balanced | internal nodes(not in the leaves) | Comparable
| AA tree | balanced | | Comparable
| R tree | balanced | only leaf nodes | Spatial/Range
| B tree | balanced | all nodes | Comparable
| 2-3 tree | balanced | | Comparable
| 2-3-4 tree | balanced | | Comparable 
| B+ tree | balanced | key in nodes, records in leave | Comparable
| [Trie/prefix-tree](graph/tree/trie) | | as node/path in the tree | Sequential/String
| Directed Acyclic Word Graph | | as edge/path in the tree | Sequential/String
| Ternary search tree | | as node/path in the tree | Comparable and Sequential/String
| Fibonacci heap | |
| Binomial heap | |
| Disjoint set forest | |
| C4.5 tree | | leaf has the final category | multiple attributes both continuous or not
| RIPPER | | 

R-tree, R*tree keeps the data in the leaf node. They are used for detecting if a point is on a given set of rectangles. It can also be used to work on the pairs of numbers or range of data which uses the one-dimensional feature instead of two dimensional rectangles. Unlike other trees they uses imaginary bucket to fill in the intermediate nodes. 

Trie and DAWG are useful for strings.

R-trees, B-trees, 2-3 tree, 2-3-4 tree and their variants are useful when the data is in disc-drive and it cannot fit in memory(RAM). This is because the nodes are compressed and they require less read from disk drive.

All these search trees can be used for sorting and growing sorted data incrementally. 

C4.5 and RIPPER are examples of decision trees. C4.5 is the decision tree built using the entropy while RIPPER is built using some logic. Both of them are classifiers and used for prediction.

[image for C4.5 and RIPPER]

#### Subset sum and Knapsack algorithms

Please refer to [sum related problems](approaches/dynamic_programming/sum/).

#### Graph algorithms

##### Shorted path

For non-negative weighted graph, shortest path can be calculated by creating a rooted tree. Breadth-first-search can find the shortest path of unweighted graph. Dijkstra algorithm is the extension of breadth-first search that works on weighted graph as well. The Dijkstra uses greedy approach to evaluate sub-problems and dynamic approach to memorize the path weight to attain the final result. 

![shortest path](shortest_path.svg)

The Bellman-ford algorithm uses rooted tree but it checks the existence of negative cycle that makes the shortest path calculation impossible. And on the contrary to Dijkstra it works for negative weight. 

All the rooted-tree approach finds single source shortest path.

There is also algorithm for all pairs shortest path. Floyd-Warshall's algorithm does that(which approach ??) .

##### Minimum spanning tree 

The minimum spanning tree can be calculated by Kruskal's greedy strategy. Like most of the greedy strategy it requires sorting. 

#### Creative problem solving and algorithms

Creativity is the novel way to solve problem in real world. One of the process to generate multiple creative ways to a problem is to use mind-map. The mind-map may contain all the algorithms and approaches for number and graph problems. It can help us to convert a real-world problem to one of such algorithmic problems. Finally we can solve the problem as we solve the algorithmic problems we have solved earlier.

![mindmap](https://cloud.githubusercontent.com/assets/973414/15445415/17623d9e-1eb3-11e6-9c9d-a97d59791845.png)

Here are some examples of [creative problem solving](creative_problem_solving).
TODO, use C-K theory to solve problem.

#### Optimization and Speedup

There are three ways to speedup the algorithms,

- Decision tree pruning.
- Memoization and tabulation.
- Parallelization.

###### Decision tree pruning

Partition based algorithms and greedy approach gain speedup by decision tree pruning. 

In greedy approach, a localy optimized choice is made. And the problem is left with typically one smaller subproblem to be solved rather than multiple subproblems. Usually greedy approach is top-down.

###### Memoization and tabulation

The dynamic programming subproblems can be represented as directed subproblem graph. Each vertex represent the subproblem. And the directed edges represent the dependency.

The dynamic programming reduce the number of times the vertices/subproblems to be calculated to one. It is done by memoization or tabulation(time-memory trade-off). And from depth-first-search we know the traversal time is O(|V| + |E|). Typically, the time to compute the solution to a subproblem is proportional to the degree of the corresponding vertex in the subproblem graph.

###### Parallelization

Parallel programming is applied by data-partitioning. Popular parallel programming patterns are pipeline-pattern, map-reduce pattern or worker-pool pattern.


#### Transformations

| Transformation | Reversibility | Data loss
| --- | --- | ---
| hash | no | yes
| md5 | no | yes
| SHA | no | yes
| Discrete-Cosine | yes | yes
| Move-to-front | yes | no
| Borrows-Wheeler | yes | no


#### Popular problems and approaches

1. Subset sum problem.
2. Knapsack problem.
3. Longest common sub-string problem.
4. Minimum Spanning tree.
5. Shortest path.
6. Minimum vertex cover
7. Hamiltonian cycle

Apart from the summary, we need to invest time for the problem and think carefully and let the mind wonder. Creativity does not work when we have narrow vision and when we are in rush. All these algorithms are the parts of our mind to move forward while our insight is the head-light that takes us to solving the problem. 




