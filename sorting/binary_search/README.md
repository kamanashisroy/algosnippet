

Binary search takes `O(log n)` time for sorted random-access container. For linked-list or non-random access ordered containers it takes `O(n)`.

C++ STL library
===============

```C++
#include <algorithm>
#include <vector>

...
...

vector<int> given = {1,2,3};

// returns true/false
std::binary_search(given.begin(), given.end(), 2);

// returns multiple nodes that are equal
auto range = std::equal_range(given.begin(), given.end(), 2);

// gives position of 2
std::lower_bound(given.begin(), given.end(), 2);

// gives position of 3
std::upper_bound(given.begin(), given.end(), 2);
```

Note `std::lower_bound()` can be used to do insertion sort and merge.

And `std::partition()` and `std::stable_partition()` can be used to do quick-sort and quick-select.

Python 
======

`bisect` module contains `bisect_left()` and `bisect_right()` that does binary search.

```python
from bisect import bisect_left

a = [1,2,3,4] # sorted

# insert x in sorted order
a.insert(bisect.bisect_left(a, 3, 0, len(a)), 3)

# insert x in sorted order(before)
a.insort_left(a, 3, 0, len(a))

# insert x in sorted order(after)
a.insort_right(a, 3, 0, len(a))

```


