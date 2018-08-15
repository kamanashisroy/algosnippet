
C++ STL library
===============

```C++
#include <algorithm>
#include <forward_list>

...
...

forward_list<int> left = {1,2,3};
forward_list<int> right = {1,2,3};
forward_list<int> result;

merge(left.begin(),left.end(),right.begin(),right.end(),result.begin());

```

Python 
======

`merge` is available in `heapq` library. It creates a sorted list.

```python
from heapq import merge

left = [1,2,3]
right = [4,5,6]

print(list(merge(left,right)))
```
