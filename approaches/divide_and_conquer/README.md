
Popular divide and conquer algoritms
=======================================

- bisect/binary search

```
    def bin_search(self, nums: List[int], target: int, lo: int, hi: int):

        '''
                            INITIALIZATION
        '''
        result = -1
        begin = lo  # inclusive
        end = hi    # exclusive
        # sanity check
        if begin >= end or begin > len(nums):
            return -1
        
        while True:
            '''
                            TERMIMATION
            '''
            if begin == end:    # Termination
                '''
                TERMINATION
                '''
                break
            if nums[begin] == target:
                '''
                BASE CASE
                '''
                result = begin  # base case
                break
            mid = (begin+end) >> 1
            midnum = nums[mid]
            if midnum == target:
                # found
                result = mid
                break
            elif midnum < target:
                '''
                            MAINTENANCE RIGHT
                '''
                begin = mid+1   # Must advance +1 to avoid infinite loop
            elif target < nums[mid]:
                '''
                            MAINTENANCE LEFT
                '''
                end = mid       # Advance left
        return result
```

Links
========

- [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)

