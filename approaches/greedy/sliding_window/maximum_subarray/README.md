
Kadane's algorithm
=====================

Kadane's algorithm uses `branch and bound` and `greedy approach`.

```python


class sliding_window:
    def __init__(self, nums: List[int], score : int):
        self.nums = nums
        self.pos = -1
        self.lpos = 0
        self.rpos = -1
        self.score = score
    
    def calc_score_right(self, rpos: int) -> int:
        assert(rpos >= self.pos)
        return self.nums[rpos]
    
    def calc_score_left(self, lpos: int) -> int:
        assert(lpos < self.pos)
        return self.nums[lpos]

    def fixup_window_border(self) -> int:
        self.pos += 1
        
        # window has to contain self.pos
        if self.rpos < self.pos:
            # move rpos right
            rscore = self.calc_score_right(self.pos)
            self.score += rscore
            self.rpos = self.pos
            
        if self.score <= 0:                     # Kadane's Branch and Bound
            self.lpos = self.rpos = self.pos
            self.score = self.nums[self.pos]
            
        if self.lpos < self.pos:                # greedy left prune
            lscore = self.calc_score_left(self.lpos)
            if (self.score - lscore) > self.score:
                self.lpos += 1
                self.score -= lscore
        
        #print(self)
        return self.score
    
    def __repr__(self):
        return '<%d,l=%d,r=%d,s=%d>' % (self.pos, self.lpos, self.rpos, self.score)
    
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        N = len(nums)
        mysln = sliding_window(nums, 0)
        
        return max([mysln.fixup_window_border() for _ in range(N)])
```


Links
=======

- [Kadane's algorithm for Maximum subarray problem](https://en.wikipedia.org/wiki/Maximum_subarray_problem)
- [Cut a strip](https://www.hackerrank.com/contests/w36/challenges/cut-a-strip)

