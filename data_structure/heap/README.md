
Heap implementations are available in the subdirectories.

C++ STL implementation
========================

Python implementation
========================

The `heapq` library contains heap implementations.

```python
from heapq import heappush, heappop

heap = []
heappush(heap, 3)
heappush(heap, 2)
heappush(heap, 1)

print(heappop())

```
#### Floyd's Theta(n) heap creation

[cxx source](binary_heap/cxx/src/dary_heap.cc)


In the following heap-creation algorithm, it starts from the bottom of the heap and goes to the top.

```
        // starting from the leaf nodes
        for(std::size_t i = x.size()-1;i;--i) {
```

And it swaps the node if mean-heap property does not hold. So there is `Theta(n)` such work. And in each case there is a bubble-down.

Now a heap is balanced tree, thus the half of the nodes are leaves.

- n/2 nodes have 0 bubble-down.
- n/4 nodes have 1 bubble-down
- n/8 nodes have 3 bubble-down

So there is `h*n/(2^(h+1))` bubble down in h level.
So there is total, Sum(`h*n/(2^(h+1))`) bubble down where h in range(0,floor(log n)).

Note that the,

```
1/2 + 1/4 + 1/8 + 1/16 .... = 1
```

So there is at most `n*1` swap in bubble-down step.

Finally the time complexity is Theta(n+n) = Theta(n).


```
    template<const std::size_t order, typename KT>
    void make_dary_heap(std::vector<KT>& x) {
        static_assert(order != 0);
        // make bottom up heap Floyd's Theta(n) algorithm
        // starting from the leaf nodes
        for(std::size_t i = x.size()-1;i;--i) {

            // compare with the parent node
            const std::size_t pi = dary_heap_parent(i,order);
            if(x[pi] <= x[i]) { // check minheap property
                continue; // already a minheap
            }

            // fix the minheap property
            std::swap(x[pi],x[i]);

            // bubble down the minheap
            std::size_t ibubble = i;
            for(std::size_t ibegin = dary_heap_child(ibubble, order); ibegin < x.size(); ibegin = dary_heap_child(ibubble, order)) {
                // bubble down
                const std::size_t iend = ibegin+(1<<order);
                std::size_t imin = ibegin;
                for(std::size_t ii = ibegin+1; (ii < x.size()) && (ii < iend); ii++) {
                    if(x[imin] > x[ii]) {
                        imin = ii;
                    }
                }
                if(x[ibubble] <= x[imin]) {
                    // heap property holds
                    break;
                } else {
                    std::swap(x[imin],x[ibubble]);
                    ibubble = imin;
                }
            } // while
        } // for
    }
```

- [Find running median](https://www.hackerrank.com/challenges/find-the-running-median/problem)

