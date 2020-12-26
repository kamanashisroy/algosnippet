#!python

class Solution:
    def subset_sum(self, nums, target):
        memo = dict()
        memo[0] = 1                    # root
        N = len(nums)
        
        for x in nums:                 # expand edges through x (induction step)
            memo_next = dict()
            for k in memo.keys():
                memo_next[k] = 1
                memo_next[k+x] = 1
            memo = memo_next
            if target in memo:
                return True
            
        return False                   # no relaxation in decision problem

