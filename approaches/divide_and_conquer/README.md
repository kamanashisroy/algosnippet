
Popular divide and conquer algoritms
=======================================

#### bisect/binary search

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

It is possible to use binary search to find kth element in a list of sorted-list.

```
def kthOfPiles(givenPiles, k, count):
    '''
    parameters
    ==========
    givenPiles  are list of sorted list
    count   is the total number of
    k       is the target index in range [0..count-1]
    '''
    begins = [0 for pile in givenPiles]
    ends = [len(pile) for pile in givenPiles]
    #print('finding k=', k, 'count=', count)

    for pileidx,pivotpile in enumerate(givenPiles):

        while begins[pileidx] < ends[pileidx]:
            mid = (begins[pileidx]+ends[pileidx])>>1
            midval = pivotpile[mid]

            smaller_count = 0
            smaller_right_count = 0
            for pile in givenPiles:
                smaller_count += bisect_left(pile,midval)
                smaller_right_count += bisect_right(pile,midval)

            #print('check midval', midval,smaller_count,k,smaller_right_count)
            if smaller_count <= k and k < smaller_right_count:
                return midval
            elif smaller_count > k:
                ends[pileidx] = mid
            else:
                begins[pileidx] = mid+1

    return -1

def medianOfPiles(givenPiles,count=None):
    '''
    Find statistical median
    Parameters:
    givenPiles  are list of sorted list
    '''
    if not givenPiles:
        return -1 # cannot find median

    if count is None:
        count = 0
        for pile in givenPiles:
            count += len(pile)

    # get mid floor
    target_mid = count >> 1
    midval = kthOfPiles(givenPiles, target_mid, count)
    if 0 == (count&1):
        midval += kthOfPiles(givenPiles, target_mid-1, count)
        midval /= 2

    return '%.1f' % round(midval,1)
```

Coupling this above binary search with patience-sort, gives a valuable technique.

- [Find running median](https://www.hackerrank.com/challenges/find-the-running-median/problem)

#### Quick select

```
def selectPvt(nums: List[int], begin:int, end:int) -> int:
    for i in range(begin,min(end,begin+3)):
        for j in range(i,begin,-1):
            if nums[j] < nums[j-1]:
                nums[j],nums[j-1] = nums[j-1],nums[j]
            else:
                break
    return (begin+end) >> 1
 
def findKthLargest(nums: List[int], k: int) -> int:
    
    begin = 0
    end = len(nums)
    
    k = len(nums)-k
    
    while begin < end:
        
        if (begin+1) == end:
            return nums[begin] # no more moves
        
        assert (end-begin) >= 2
        
        pidx = selectPvt(nums,begin,end)
        
        # swap pivote to end
        nums[pidx],nums[end-1] = nums[end-1],nums[pidx]
        
        pvt = nums[end-1]
        lo = begin
        hi = end-2
        
        while lo <= hi:
            
            if nums[lo] < pvt:
                lo += 1
            elif nums[hi] >= pvt:
                hi -= 1
            else:
                if nums[lo] > nums[hi]:
                    nums[lo],nums[hi] = nums[hi],nums[lo]
                    hi -= 1
        
        # swap pivot to middle
        nums[lo],nums[end-1] = nums[end-1],nums[lo]
        if lo == k:
            return nums[lo]
        elif lo < k:
            begin = lo+1
        else:
            end = lo
        
```

Links
========

- [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
- [Element Appearing More Than 25% In Sorted Array](https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/)
- [Form Array by Concatenating Subarrays of Another Array](https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/)
- 2 Dimentional binary search
    - [Seperate squares 2](https://leetcode.com/problems/separate-squares-ii/description/)
        - [My solution](https://leetcode.com/problems/separate-squares-ii/solutions/6702875/binary-search-on-sorted-array-of-y-coord-and-prefix-sum)


