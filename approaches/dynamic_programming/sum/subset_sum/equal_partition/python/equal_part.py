#!python

class Solution:
    def equal_part(self, nums):
        total = sum(nums)
        if (total & 1) == 1:
            return False # it is not possible to do equal partition when false
        
        bipart = total>>1
        
        memo = dict()
        memo[0] = 1
        N = len(nums)
        
        for x in nums:
            memo_next = dict()
            for k in memo.keys():
                memo_next[k] = 1
                memo_next[k+x] = 1
            memo = memo_next
            #print(memo)
            if bipart in memo:
                return True
            
        return False
