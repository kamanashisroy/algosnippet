

It can be done in following popular ways,


  algorithm    |    time complexity    |   Worst case time complexity
  ---------    |    --------------     |   --------------------------
 quick-select  |        O(n)           |          O(n^2)
 intro-select  |        O(n)           |          O(n)
 heap-select   |    O(n + k * log(n))  |         O(n + k * log(n))

Note the cost of `heapify()`(bottom up heap construction) is `O(n)`.


C++ STL library
===============

It uses intro-select.(sometimes heap-select). Time complexity is `O(n * log n)`.

```C++
#include <algorithm>
#include <vector>

...
...

vector<int> given{10,1,6,3};

nth_element(given.begin(),given.begin()+2,given.end());
```

Python 
======

`nlargest()` and `nsmallest()` is available in `heapq` library. It uses heap-select algorithm. Time complexity is `O(n * log n)`.

Time complexity is `O(n * log n)`.

```python
from heapq import nsmallest

given = [8,5,6,9]

print(list(nsmallest(given,2))[2])
```
