
Binary Search has O(n log n) runtime.

C/C++ bisect
=============

In c/c++ binary search is implemented in the following functions.

- `binary_search`
- `lower_bound`
- `upper_bound`
- `equal_range`

Python bisect
=============

- `bisect_left`
- `bisect_right`

Binary Search like 3 way partition
===================================


Like the 3-way-quick-sort partitions the given unsorted array into three parts by the pivote,
binary search can be used to partition a sorted array into three parts using the pivote.

```
 [smaller] [equal] [bigger]
```

Smaller partition can be done by,
    - *skipping the left* when `content[mid] < pvt`,
    - *skipping the right* when `pvt <= content[mid]`

```
def bin_search_left(content, pvt, begin=0, end=None):
    '''
    Algorithm searches in the range [begin,end) .

    Returns the last index of x where content[x] < pvt
            , otherwise returns -1 when all elements are equal or bigger
    '''
    # avoid overflow
    end = len(content) if end is None else min(end,len(content))

    while (begin+1) < end:
        mid = (begin+end) >> 1

        if content[mid] < pvt:
            # skip left
            begin = mid
        else: # when pvt <= content[begin]
            # skip right
            end = mid

    return begin if content[begin] < pvt else begin-1
```

Bigger partition can be done by,
    - *Skipping the left* when `content[mid] <= pvt`
    - *skipping the right* when `pvt < content[mid]`

```
def bin_search_right(content, pvt, begin=0, end=None):
    '''
    Algorithm searches in the range [begin,end) .

    Returns the first index of x where pvt < content[x]
            , otherwise returns end when all elements are smaller or equal.
    '''
    # avoid overflow
    end = len(content) if end is None else min(end,len(content))

    while (begin+1) < end:
        # divide
        mid = (begin+end) >> 1

        if content[mid] <= pvt:
            # skip left content
            begin = mid
        else: # when pvt < content[mid]:
            # skip right contents
            end = mid
 
    return begin if pvt < content[begin] else (begin+1)
```

Now when the `bin_search_right() == end` then all the elements are equal or smaller than the pivote.


Equal partition selection is done by,
    - *Skipping the left* when `content[mid] < pvt`
    - *Skipping the right* when `pvt < content[mid]`
    - return when equal

```
def bin_search_equal(content, pvt, begin=0, end=None):
    '''
    It searches for the exact match in sorted content.
    Returns the index of exact match, None otherwise
    '''
    end = len(content) if end is None else min(end,len(content))

    while (begin+1) < end:
        mid = (begin+end)>>1

        if content[mid] == pvt:
            return mid
        elif content[mid] < pvt:
            # skip left
            begin = mid
        else: # when pvt < content[mid]
            end = mid
    
    return begin if content[begin] == pvt else None
```

Links
======

**Warning: binary search algorithms are hard to get it right**

- [Capacity to ship packages within D days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/)
- [2187. Minimum Time to Complete Trips](https://leetcode.com/contest/weekly-contest-282/problems/minimum-time-to-complete-trips/)
- Very tricky [2141. Maximum Running Time of N Computers](https://leetcode.com/problems/maximum-running-time-of-n-computers/)
- Hardest [2071. Maximum Number of Tasks You Can Assign](https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/)


